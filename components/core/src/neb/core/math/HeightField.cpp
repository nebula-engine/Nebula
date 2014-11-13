#include <iomanip>
#include <iostream>
#include <neb/core/rand.hpp>
#include <neb/core/math/HeightField.hpp>
#include <limits>
#include <type_traits>
#include <cmath>
#include <cassert>

typedef neb::math::HeightField THIS;


THIS::HeightField(unsigned int r, unsigned int c)
{
	_M_r = r;
	_M_c = c;
}
void	THIS::alloc()
{
	_M_z = new float[_M_r * _M_c];
}
void	THIS::createRandom()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	alloc();

	srand(time(NULL));

	for(unsigned int j = 0; j < _M_c; j++) {
		for(unsigned int i = 0; i < _M_r; i++) {
			_M_z[at(i,j)] = (float)myrand();
		}
	}

}
float const		THIS::min() const
{
	float m = std::numeric_limits<float>::max();

	for(unsigned int i = 0; i < _M_r; i++)
	{
		for(unsigned int j = 0; j < _M_c; j++)
		{
			float s = _M_z[at(i,j)];
			if(s < m) m = s;
		}
	}
	return m;
}
float const		THIS::max() const
{
	float m = std::numeric_limits<float>::min();

	for(unsigned int i = 0; i < _M_r; i++)
	{
		for(unsigned int j = 0; j < _M_c; j++)
		{
			float s = _M_z[at(i,j)];
			if(s > m) m = s;
		}
	}
	return m;
}
int	THIS::at(int i, int j) const
{
	i = (i + _M_r) % _M_r;
	j = (j + _M_c) % _M_c;
	return i * _M_c + j;
}
void	THIS::filterc(float factor)
{


	// determine width based on distance value
	int width = _M_r / 2;

	float center = exp(0);

	for(unsigned int i = 0; i < (_M_r / 2); i++)
	{
		float den = exp(-float(i) * factor);
		if(den < (0.05 * center))
		{
			width = i;
			break;
		}
	}

	std::cout << __PRETTY_FUNCTION__ << " width=" << width << std::endl;

	int a = -width;
	int b = width + 1;

	float sum;
	float den;

	int w = 2 * width + 1;
	float* dist = new float[w*w];

	for(int k = a; k < b; k++) {
		for(int l = a; l < b; l++) {
			dist[(k+width) * w + (l+width)] = sqrt(float(k*k) + float(l*l)) * factor;
		}
	}

	for(unsigned int i = 0; i < _M_r; i++)
	{
		std::cout << std::setw(8) << i << "/ " << _M_r << std::endl;
		for(unsigned int j = 0; j < _M_c; j++)
		{
			sum = 0;
			den = 0;
			for(int k = a; k < b; k++)
			{
				for(int l = a; l < b; l++)
				{
					float d = exp(-dist[(k+width) * w + (l+width)]);

					sum += _M_z[at(i + k, j + l)] * d;

					den += d;

					//std::cout<< " k,l = " << k << " " << l<< " dist = " << dist<< std::endl;

				}
			}

			float newS = sum / den;

			//std::cout<< " newS = " << newS<< " sum = " << sum<< " den = " << den<< std::endl;

			_M_z[at(i,j)] = newS;
		}
	}
}
void	THIS::filter(unsigned int width)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	int n = (width * 2 + 1) * (width * 2 + 1);

	int a = -width;
	int b = width + 1;

	float sum;

	for(unsigned int i = 0; i < _M_r; i++)
	{
		for(unsigned int j = 0; j < _M_c; j++)
		{
			sum = 0;
			for(int k = a; k < b; k++)
			{
				for(int l = a; l < b; l++)
				{
					sum += _M_z[at(i + k, j + l)];
				}
			}
			//short oldS = _M_z[at(i,j)].height;
			float newS = sum / (float)n;
			/*std::cout
			  << " oldS = " << oldS
			  << " newS = " << newS
			  << " sum = " << sum
			  << " n = " << n
			  << std::endl;*/
			_M_z[at(i,j)] = newS;
		}
	}
}
void	THIS::normalize(float a, float b)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	float minH = min();
	float maxH = max();

	float slope = (b - a) / (maxH - minH);

	for(unsigned int i = 0; i < _M_r; i++)
	{
		for(unsigned int j = 0; j < _M_c; j++)
		{
			float& s = _M_z[at(i,j)];

			float l = slope * (s - minH) + a;

			/*	std::cout
				<< " s = " << s
				<< " l = " << l
				<< " new = " << (short)l
				<< " slope = " << slope
				<< std::endl;*/
			s = (float)l;
		}
	}
}
float const		THIS::get(int i, int j) const
{
	return _M_z[at(i,j)];
}
float			THIS::get(int i, int j)
{
	return _M_z[at(i,j)];
}

void			THIS::operator+=(THIS const & hf)
{
	assert(hf._M_r == _M_r);
	assert(hf._M_c == _M_c);

	for(unsigned int i = 0; i < _M_r; i++)
	{
		for(unsigned int j = 0; j < _M_c; j++)
		{
			_M_z[at(i,j)] += hf.get(i,j);
		}
	}
}


void		THIS::slope(float dx, float dy)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	_M_dzdx = new float[_M_r*_M_c];
	_M_dzdy = new float[_M_r*_M_c];

	for(unsigned int i = 0; i < _M_r; i++)
	{
		for(unsigned int j = 0; j < _M_c; j++)
		{

			if(i == 0)
			{
				_M_dzdx[at(i,j)] =
					(
					 _M_z[(i+1)*_M_c + j] -
					 _M_z[(i+0)*_M_c + j]
					);// / dx;
			}
			else if(i == (_M_r-1))
			{
				_M_dzdx[at(i,j)] = 
					(
					 _M_z[(i-0)*_M_c + j] -
					 _M_z[(i-1)*_M_c + j]
					);// / dx;
			}
			else
			{
				_M_dzdx[at(i,j)] = 
					(
					 _M_z[(i+1)*_M_c + j] -
					 _M_z[(i-1)*_M_c + j]
					) / 2.0;// / dx / 2.0;
			}
			if(j == 0)
			{
				_M_dzdy[at(i,j)] = 
					(
					 _M_z[(i)*_M_c + j+1] -
					 _M_z[(i)*_M_c + j]
					);// / dy;
			}
			else if(j == (_M_c-1))
			{
				_M_dzdy[at(i,j)] = 
					(
					 _M_z[(i)*_M_c + j] -
					 _M_z[(i)*_M_c + j-1]
					);// / dy;
			}
			else
			{
				_M_dzdy[at(i,j)] = 
					(
					 _M_z[(i)*_M_c + j+1] -
					 _M_z[(i)*_M_c + j-1]
					) / 2.0;/// dy / 2.0;
			}

		}
	}
}
THIS*			THIS::mipmap(int down)
{
	// calculate size
	uint8_t r = _M_r;
	uint8_t c = _M_c;
	
	uint8_t stride = 1;

	for(int i = 0; i < down; i++)
	{
		assert(((r-1) % 2) == 0);
		assert(((c-1) % 2) == 0);

		r = (r-1) / 2 + 1;
		c = (c-1) / 2 + 1;

		stride *= 2;
	}

	std::cout << "mipmap" << std::endl;
	std::cout << "original " << _M_r << " " << _M_c << std::endl;
	std::cout << "new      " << r << " " << c << std::endl;
	
	// create object
	THIS* hf = new THIS(r,c);
	hf->alloc();
	
	// copy data
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			hf->_M_z[hf->at(i,j)] = _M_z[at(i*stride, j*stride)];
		}
	}
	
	return hf;
}















