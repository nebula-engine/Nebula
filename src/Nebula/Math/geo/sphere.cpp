#include <stdio.h>

#include <Nebula/Math/geo/polyhedron.hh>

//math::geo::thin_cyl::cylinder(float 
math::geo::sphere::sphere(float r, int slices, int stacks) {
/*	
	printf( "tris:  %i\n"
		"quads: %i\n",nt_,nq_);
	
	vertices_ = new math::geo::vertex[nv_];
	tris_ = new math::geo::tri[nt_];
	quads_ = new math::geo::quad[nq_];
	
	vertices_ = new math::geo::vertex[1000];
	tris_ = new math::geo::tri[1000];
	quads_ = new math::geo::quad[1000];


	printf("arrays allocated\n");
	
	
	
	math::geo::tri* north = tris_;
	math::geo::tri* south = tris_ + slices;

	math::geo::vertex poles[2];
	
	poles[0].p = vec3(0,-r,0);
	poles[1].p = vec3(0, r,0);
	
	poles[0].n = vec3(0,-1,0);
	poles[1].n = vec3(0, 1,0);
	
	math::geo::vertex* interior = vertices_ + 2;
	
	float theta;
	float phi;
	
	for( int a = 0; a < slices; ++a )
	{
		theta = a * 2.0f * M_PI / (float)slices;
		
		for( int b = 0; b < (stacks-1); ++b )
		{
			phi = -M_PI / 2.0f + (b+1) * M_PI / (float)stacks;

			//printf("%f %f %f %f\n",theta/M_PI,phi/M_PI,cos(theta),cos(phi));
			
			
			
			vec3 v(
					r * cos(theta) * cos(phi),
					r * sin(phi),
					r * sin(theta) * cos(phi));
			
			
			//printf("% 5f % 5f % 5f\n",v.x,v.y,v.z);
			//v.print();
			
			
			interior[a*slices+b].p = v;
			interior[a*slices+b].n = v;
			glm::normalize(interior[a*slices+b].n);
		}
	}
	
	for( int a0 = 0; a0 < slices; ++a0 )
	{
		int a1 = (a0+1) % slices;
		
		north[a0].v_[2] = interior[a0*slices + stacks-2];
		north[a0].v_[1] = interior[a1*slices + stacks-2];
		north[a0].v_[0] = poles[1];

		south[a0].v_[2] = interior[a1*slices + 0];
		south[a0].v_[1] = interior[a0*slices + 0];
		south[a0].v_[0] = poles[0];

		for( int b0 = 0; b0 < (stacks-2); ++b0 )
		{
			int b1 = b0 + 1;
			
			printf("a0 % 2i a1 % 2i b0 % 2i b1 % 2i\n",a0,a1,b0,b1);
			
			quads_[a0*slices + b0].v_[3] = interior[a0*slices + b0];
			quads_[a0*slices + b0].v_[2] = interior[a1*slices + b0];
			quads_[a0*slices + b0].v_[1] = interior[a1*slices + b1];
			quads_[a0*slices + b0].v_[0] = interior[a0*slices + b1];
		}
	}

	if( flag_ & PER_FACE_NORMAL )
	{
		for( int a0 = 0; a0 < slices; ++a0 )
		{
			north[a0].reset_normals();
			south[a0].reset_normals();

			for( int b0 = 0; b0 < (stacks-1); ++b0 )
			{
				quads_[a0*slices + b0].reset_normals();
			}
		}

	}
*/
}

