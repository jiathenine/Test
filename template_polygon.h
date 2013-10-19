#ifndef TEST_POLYGON_TEMPLATE_POLYGON_H_
#define TEST_POLYGON_TEMPLATE_POLYGON_H_
#include<memory>
#include<string>
#include<math.h>
struct point{
	point(float f1 = 0,float f2 = 0):x(f1),y(f2){ };
	
	point* operator=(point const& rcp)
	{
		x = rcp.x;
		y = rcp.y;
	}
	float x;
	float y;

};
point operator+(point const& rrp,point const& lrp)
{
	return  point(rrp.x + lrp.x,rrp.y + lrp.y);
	
}
point operator-(point const& rrp,point const& lrp)
{
	
	return  point(rrp.x - lrp.x,rrp.y - lrp.y);
}
float abs(point const& rrp,point const& lrp)
{
	float absFlo = sqrt ( (rrp.x - lrp.x)*(rrp.x - lrp.x) + (rrp.y - lrp.y)*(rrp.y - lrp.y));
	return absFlo;
}
//line :aX - b = Y
struct line{
	line(point const& rhp,point const& lhp)
	{
		a =  (rhp.y - lhp.y) / (rhp.x - lhp.x);
		b = a * rhp.x - rhp.y;
	}
	
	float slope()const
	{
		return a;
	}
	float a;
	float b;
};


class polygon_base{
public:
	//clockwise vector point
	polygon_base(point const* coor,std::size_t sz)
		:coordinate(new point[sz]),size(sz)
	{
		point *beg = coordinate;
		point *end = coordinate + sz;
		while(beg != end){
			*beg++ = *coor++;
		}
		
	}
	bool OutOrIn(point const& rp)const
	{
		float sumAngle = 0.0f;
		//count included angle for two line
		for(point const* ip = coordinate; ip != end();++ip){
			//cp is next point of ths polygon round
			point const* cp = ip+1;
			if(cp == coordinate)
				cp = coordinate;
			line l1(*ip,rp),l2(*(ip+1),rp);
			//
			float subAngle =std::atanf( ( l1.slope() - l2.slope() ) / (1 - l1.slope() * l2.slope()) ) ;
			sumAngle += subAngle;
		}
		if(sumAngle >359.0f && sumAngle < 361.0f)
			return 1;
		else 
			return 0;
	}
	inline point const* end()const
	{
		return coordinate + size;
	}
	inline point* end()
	{
		return coordinate + size;
	}
private:
	point *const coordinate;
	std::size_t size;
	bool model;
};



#endif