// completed with sanjayb3, aryana9, sureban2

#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name;
	}
	
  	string getName() {
		return name_;
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		width_ = width;
		length_ = length;
	}
	
  	double getArea() const {
		return (double) (length_ * width_);
	}
	
  	double getVolume() const {
		return (double) (0);
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		return Rectangle<T>(width_ + rec.width_, length_ + rec.length_);
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		return Rectangle<T>(
			max((T)0, width_ - rec.width_),
			max((T)0, length_ - rec.length_)
		);	
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
        T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_ = radius;
	}
	
  	double getArea() const{
		return (double) (M_PI * radius_ * radius_);
	}
	
 	double getVolume() const{
		return (double) (0);
	}
	
  	Circle operator + (const Circle& cir){
		return Circle(radius_ + cir.radius_);
	}
	
	Circle operator - (const Circle& cir){
		return Circle(max(0.0, radius_ - cir.radius_));
	} 

	double getRadius() const { 
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;
	}

  	double getVolume() const {
		return (double) ((4.0 / 3.0) * M_PI * radius_ * radius_ * radius_);
	}	
	
  	double getArea() const {
		return (double) (4.0 * M_PI * radius_ * radius_);
	}

	Sphere operator + (const Sphere& sph) {
		return Sphere(radius_ + sph.radius_);
	}

	Sphere operator - (const Sphere& sph) {
		return Sphere(max(0.0, radius_ - sph.radius_));
	} 
	
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		length_ = length;
		width_ = width;
		height_ = height;
	}
	
  	double getVolume() const {
		return (double) (length_ * width_ * height_);
	}
  	
	double getArea() const {
		return (double) (2 * (width_ * length_ + width_ * height_ + length_ * height_));
	}
	
	RectPrism operator + (const RectPrism& rectp){
		return RectPrism(width_ + rectp.width_, length_ + rectp.length_, height_ + rectp.height_);
	}
	
	RectPrism operator - (const RectPrism& rectp){
		return RectPrism(
			max(0.0, width_ - rectp.width_),
			max(0.0, length_ - rectp.length_),
			max(0.0, height_ - rectp.height_)
		);	
	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
  
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a list of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
    list<Shape*> shapes;
    ifstream ifs(file_name, std::ifstream::in);
    int num_shapes;
    ifs >> num_shapes;
    for(int i = 0; i < num_shapes; i++) {
        string name;
        ifs >> name;

        if(name == "Circle") {
            double radius;
            ifs >> radius;
            Shape* shape_ptr = new Circle(radius); 
            shapes.push_back(shape_ptr);
        }
        else if(name == "Sphere") {
            double radius;
            ifs >> radius;
            Shape* shape_ptr = new Sphere(radius); 
            shapes.push_back(shape_ptr);
        }
        else if(name == "Rectangle") {
            double width, length;
            ifs >> width;
            ifs >> length;
            Shape* shape_ptr = new Rectangle<double>(width, length); 
            shapes.push_back(shape_ptr);
        }
        else if(name == "RectPrism") {
            double width, length, height;
            ifs >> width; 
            ifs >> length;
            ifs >> height;
            Shape* shape_ptr = new RectPrism(width, length, height); 
            shapes.push_back(shape_ptr);
        }
    }
    ifs.close();
	return shapes;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++) {
   		if((*it)->getArea() > max_area)
		{
			max_area = (*it)->getArea();
		}
}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++) {
   		if((*it)->getVolume() > max_volume)
		{
			max_volume = (*it)->getVolume();
		}
	}
	return max_volume;
	
}
#endif