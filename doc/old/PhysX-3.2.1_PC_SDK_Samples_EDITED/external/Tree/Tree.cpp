
#include "Tree.h"

#include <stdio.h>
#include <string.h>

template <class T>				TreeGroup::TreeGroup(const char* name, size_t count)
	: m_data(NULL)
	, mParent(NULL)
{
	if (MAX_COUNT == count)
		count = strlen(name);
	mName = new char[count + 1];
	strncpy(mName, name, count);
	mName[count] = '\0';
}
template <class T>				TreeGroup::TreeGroup(TreeGroup* group)
	: m_data(group->m_data)
	, mParent(NULL)
{
	mName = new char[strlen(group->getName()) + 1];
	strcpy(mName, group->getName());
}
template <class T>				TreeGroup::TreeGroup(SampleCreator Data, const char* name, size_t count)
	: m_data(Data)
	, mParent(NULL)
{
	PX_ASSERT(Data);

	if (MAX_COUNT == count)
		count = strlen(name);
	mName = new char[count + 1];
	strncpy(mName, name, count);
	mName[count] = '\0';
}
template <class T>				TreeGroup::~TreeGroup()
{
	if (!isData())
	{
		for (PxU32 i = 0; i < mChildren.size(); i++)
			delete mChildren[i];

		delete[] mName;
	}
}

template <class T>	void		TreeGroup::addLeaf(SampleCreator Data, const char* name, size_t count)
{
	/*
	Automatically creates a child TreeGroup representing the Data passed. A DataInterface instance
	shouldn't be added multiple times, since it is owned by this TreeGroup after the call.
	*/

	PX_ASSERT(!isData() && Data);
	TreeGroup* TreeGroup = new TreeGroup(Data, name, count);
	addGroup(TreeGroup);
}
template <class T>	void		TreeGroup::addGroup(TreeGroup* group)
{
	/*
	Adds a child TreeGroup to this TreeGroup. After this call the group is owned by this. 
	A TreeGroup can't be added multiple times.
	*/
	PX_ASSERT(group && !group->getParent());
	mChildren.pushBack(group);
	group->mParent = this;
}
template <class T>	TreeGroup*	TreeGroup::addPath(SampleArray<TreeGroup*>& path)
{
	/*
	Adds a copy of path to this group avoiding duplicates. Returns the copy of the last element in path.
	*/

	if (path.size() == 0)
		return NULL;

	TreeGroup* current = this;
	for (unsigned i = 0; i < path.size(); i++)
	{
		TreeGroup* pathGroup = path[i];
		TreeGroup* child = current->getChildByName(pathGroup->getName());
		if (!child)
		{
			child = new TreeGroup(pathGroup);
			current->addGroup(child);
		}
		current = child;
	}
	
	return current;
}
template <class T>	TreeGroup*	TreeGroup::deepCopy()
{
	/*
	Deep copy of all the group data, except the Datas themselves. The copy is returned as a root.
	*/
	
	TreeGroup* groupCopy = new TreeGroup(this);

	for (unsigned i = 0; i < mChildren.size(); i++)
	{
		TreeGroup* childCopy = mChildren[i]->deepCopy();
		groupCopy->addGroup(childCopy);
	}

	return groupCopy;
}
template <class T>	const char* TreeGroup::getName() const
{
	/*
	Returns the name of the TreeGroup. If the Data group represents a single 
	Data, the name of the Data is returned instead.
	*/
	return mName;
}
template <class T>	void		TreeGroup::getPath(SampleArray<TreeGroup*>& path)
{
	/*
	Fills all TreeGroup instances into path starting with this->getRoot() and ending with this. 
	*/

	if (getParent())
		getParent()->getPath(path);

	path.pushBack(this);
}
template <class T>	void		TreeGroup::getPathName(char* strBuffer, unsigned strBufferMaxLength, bool omitRoot)
{
	/*
	Prints all the TreeGroup names to strBuffer in this format:
	"RootName/Name1/Name2/.../ThisName"
	With omitRoot the root TreeGroup is omitted.
	*/

	SampleArray<TreeGroup*> path;
	getPath(path);

	unsigned charCount = 1; //\0
	for (unsigned i = omitRoot ? 1 : 0; i < path.size(); ++i)
	{
		const TreeGroup& node = *path[i];

		unsigned nodeNameLength = unsigned(strlen(node.getName()));
		if (node.getFirstChild())
			nodeNameLength += 1;

		if (charCount + nodeNameLength < strBufferMaxLength)
		{
			sprintf(strBuffer + (charCount - 1), "%s%s", node.getName(), node.getFirstChild() ? "/" : "");
			charCount += nodeNameLength;
		}
	}
}
template <class T>	TreeGroup*	TreeGroup::getGroupFromPathName(const char* pathName, bool omitRoot)
{
	/*
	Reads a path from pathName and returns the corresponding TreeGroup. 
	The format of the path has to be the same as the one used by getPathName().
	If the TreeGroup doesn't exist, NULL is returned.
	*/

	if (!omitRoot || getParent())
	{
		if (strstr(pathName, getName()) != pathName)
			return NULL;

		pathName += strlen(getName());

		if (getFirstChild())
		{
			if (strstr(pathName, "/") != pathName)
				return NULL;

			pathName += strlen("/");
		}
		else
		{
			if (pathName[0] == '\0')
				return this;
			else
				return NULL;
		}
	}

	for (unsigned i = 0; i < mChildren.size(); ++i)
	{
		TreeGroup* group = mChildren[i]->getGroupFromPathName(pathName, omitRoot);
		if (group)
			return group;
	}
	return NULL;
}
template <class T>	TreeGroup*	TreeGroup::getNextChild(TreeGroup& current)
{
	/*
	Returns the next direct child of this TreeGroup after current. If there is no next child, NULL is returned.
	The TreeGroup current has to be itself a direct child of this TreeGroup. 
	*/
	int nextIndex = getChildIndex(current) + 1;
	if (nextIndex >= int(mChildren.size()))
		return NULL;

	return mChildren[nextIndex];
}
template <class T>	TreeGroup*	TreeGroup::getPreviousChild(TreeGroup& current)
{
	/*
	Returns the previous direct child of this TreeGroup after current. If there is no previous child, NULL is returned.
	The TreeGroup current has to be itself a direct child of this TreeGroup. 
	*/
	int prevIndex = getChildIndex(current) - 1;
	if (prevIndex < 0)
		return NULL;

	return mChildren[prevIndex];
}
template <class T>	TreeGroup*	TreeGroup::getChildByName(const char* name, size_t count)
{
	/*
	Returns the child with the given name, if exists.
	*/
	if (MAX_COUNT == count)
		count = strlen(name) + 1;
	for (unsigned i = 0; i < mChildren.size(); i++)
	{
		if (strncmp(mChildren[i]->getName(), name, count) == 0)
			return mChildren[i];
	}
	return NULL;
}

template <class T>	TreeGroup*	TreeGroup::getFirstData()
{
	TreeGroup* current = getFirstLeaf();
	if (!current || current->isData())
		return current;

	return getNextData(current);
}
template <class T>	TreeGroup*	TreeGroup::getLastData()
{
	TreeGroup* current = getLastLeaf();
	if (!current || current->isData())
		return current;

	return getPreviousData(current);
}

template <class T>	TreeGroup*	TreeGroup::getNextData(TreeGroup* current)
{
	/*
	Returns the next DataGroup representing a single Data (isData() == true) within 
	the whole Data group tree rooted at this DataGroup. The current DataGroup has to be
	a descendant of this DataGroup.
	*/

	current = getNextLeaf(current);
	while (current && !current->isData())
		current = getNextLeaf(current);

	return current;
}
template <class T>	TreeGroup*	TreeGroup::getPreviousData(TreeGroup* current)
{
	current = getPreviousLeaf(current);
	while (current && !current->isData())
		current = getPreviousLeaf(current);

	return current;
}

template <class T>	unsigned	TreeGroup::getChildIndex(TreeGroup& child)
{
	PX_ASSERT(!isData());
	TreeGroup** p = mChildren.find(&child);
	PX_ASSERT(p != mChildren.end());
	return unsigned(p - mChildren.begin());
}

template <class T>	TreeGroup*	TreeGroup::getFirstLeaf()
{
	/*
	Returns the first TreeGroup representing a single Data (isData() == true) within 
	the whole Data group tree rooted at this TreeGroup. Returns NULL if there isn't such 
	a TreeGroup.
	*/
	
	TreeGroup* firstChild = getFirstChild();
	if (!firstChild)
		return this;

	return firstChild->getFirstLeaf();
}
template <class T>	TreeGroup*	TreeGroup::getLastLeaf()
{
	/*
	Returns the last TreeGroup representing a single Data (isData() == true) within 
	the whole Data group tree rooted at this TreeGroup. Returns NULL if there isn't such 
	a TreeGroup.
	*/
	TreeGroup* lastChild = getLastChild();
	if (!lastChild)
		return this;

	return lastChild->getLastLeaf();
}
template <class T>	TreeGroup*	TreeGroup::getNextLeaf(TreeGroup* current)
{
	PX_ASSERT(current);

	if (current == this)
		return NULL;

	TreeGroup* parent = current->getParent();
	if (!parent)
		return NULL;

	TreeGroup* nextSibling = parent->getNextChild(*current);
	if (nextSibling)
		return nextSibling->getFirstLeaf();
	else
		return getNextLeaf(parent);
}
template <class T>	TreeGroup*	TreeGroup::getPreviousLeaf(TreeGroup* current)
{
	/*
	Returns the previous DataGroup representing a single Data (isData() == true) within 
	the whole Data group tree rooted at this DataGroup. The current DataGroup has to be
	a descendant of this DataGroup.
	*/
	
	PX_ASSERT(current);

	if (current == this)
		return NULL;

	TreeGroup* parent = current->getParent();
	if (!parent)
		return NULL;

	TreeGroup* prevSibling = parent->getPreviousChild(*current); 
	if (prevSibling)
		return prevSibling->getLastLeaf();
	else
		return getPreviousLeaf(parent);
}

template <class T>	TreeGroup*	TreeGroup::getParent() const 
{
	/*
	Returns the parent TreeGroup, if this isn't a root. 
	*/
	return mParent;
}
template <class T>	TreeGroup*	TreeGroup::getRoot()
{
	/*
	Returns the root of this TreeGroup.
	*/
	return mParent ? mParent->getRoot() : this;
}

template <class T>	TreeGroup*	TreeGroup::getFirstChild() const
{
	/*
	Returns the first direct child of this TreeGroup. If this TreeGroup doesn't have
	any children, NULL is returned. 
	*/
	return mChildren.empty() ? NULL : mChildren.front();
}
template <class T>	TreeGroup*	TreeGroup::getLastChild() const
{
	/*
	Returns the last direct child of this TreeGroup. If this TreeGroup doesn't has
	any children, NULL is returned. 
	*/
	return mChildren.empty() ? NULL : mChildren.back();
}

template <class T>	bool		TreeGroup::isData() const
{
	/*
	Returns whether this TreeGroup corresponds to a single Data.
	*/
	return m_data != NULL;
}
template <class T>	void		TreeGroup::releaseGroups()
{
	/*
	Releases all Datas from this node and its descendants. 
	Destructing a Data groups just releases the groups and not the Datas themselves!
	*/
}
template <class T>	PxU32		TreeGroup::numChildren() const
{
	/*
	Returns the number of children
	*/
	return mChildren.size();
}



/*
	Returns the DataInterface for a TreeGroup corresponding to a single Data.
	*/
//	DataInterface& getDataInterface() { PX_ASSERT(isData()); return *m_data; }