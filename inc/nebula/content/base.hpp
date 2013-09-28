#ifndef __NEBULA_CONTENT_BASE_HPP__
#define __NEBULA_CONTENT_BASE_HPP__

#include <boost/enable_shared_from_this.hpp>

#include <jess/map.hpp>
#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/framework/types.hpp>
#include <nebula/utilities/types/content/types.hpp>
#include <nebula/utilities/types/content/universe/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
namespace content
{
class base:
public boost::enable_shared_from_this<nebula::content::base>
{
public:
base();
virtual ~base();
virtual void							init(const boost::shared_ptr<nebula::framework::app>&);
virtual void							shutdown();
virtual void							update();
virtual void							register_universe(const boost::shared_ptr<ncua::base>&);



/// physics
jess::shared_ptr<ncp::base>					physics_;
/// universes
jess::map<ncua::base>						universes_;



/// parent
boost::weak_ptr<nebula::framework::app>				parent_;

};
}
}




#endif
