
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <object.h>


int object::load(const char * filename)
{
	FILE * fp;
	size_t filesize;
	char * data;
	
	file_header fh;
	
	fp = fopen(filename, "rb");
	
	if (!fp) return 0;
	
	// read header
	fread(&fh, sizeof(file_header), 1, fp);
	
	// read positions
	fread(vertex_positions_, sizeof(float), fh.len_positions_, fp);
	
	// read normals
	fread(vertex_normals_, sizeof(float), fh.len_normals_, fp);

	// read indices
	fread(vertex_indices_, sizeof(float), fh.len_indices_, fp);
	
	fclose(fp);

}
int object::save(const char * filename)
{
	FILE * fp;
	size_t filesize;
	char * data;
	
	file_header fh;
	
	fp = fopen(filename, "wb");
	
	if (!fp) return 0;


	
	// read header
	fwrite(&fh, sizeof(file_header), 1, fp);
	
	// read positions
	fwrite(vertex_positions_, sizeof(float), fh.len_positions_, fp);
	
	// read normals
	fwrite(vertex_normals_, sizeof(float), fh.len_normals_, fp);
	
	// read indices
	fwrite(vertex_indices_, sizeof(float), fh.len_indices_, fp);
	
	fclose(fp);

}

void object::init_buffer()
{
	// position
	GLuint postion_buffer_;
	GLuint position_location = 0;

	glGenBuffers(1, &buffer_position_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_position_);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(vertex_positions),
			vertex_positions,
			GL_STATIC_DRAW);
	glVertexAttribPointer(position_location, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(position_location);

	// normal
	GLuint normal_buffer;
	GLuint normal_location = 1;

	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(vertex_normals),
			vertex_normals,
			GL_STATIC_DRAW);
	glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(normal_location);

	// index
	GLuint index_buffer;

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(vertex_indices),
			vertex_indices,
			GL_STATIC_DRAW);
}
void object::draw()
{
	//glGetFloatv(GL_MODELVIEW_MATRIX,mv_matrix);
	
	glUniformMatrix4fv(uniform_mv,1,GL_FALSE,matrix_mv);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}

