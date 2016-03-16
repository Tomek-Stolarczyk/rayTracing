/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include <algorithm>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	
	// Everything taken from http://www.dgp.toronto.edu/~karan/courses/418/Notes/BasicRayTracing.pdf
	
    if (!ray.intersection.none){

        Colour I_a = _col_ambient;
        Colour I_d = _col_diffuse;
        Colour I_s = _col_specular;

        Colour r_a = ray.intersection.mat->ambient;
        Colour r_d = ray.intersection.mat->diffuse;
        Colour r_s = ray.intersection.mat->specular;
        double alpha = ray.intersection.mat->specular_exp;

        Colour r_g = Colour();
        Colour I_spec = Colour();

        Vector3D view = Vector3D(ray.origin - ray.intersection.point);

        Vector3D n = ray.intersection.normal;
        n.normalize();

        Vector3D s = Vector3D(get_position() - ray.intersection.point);
        s.normalize();

        Vector3D c = -ray.dir;
        c.normalize();

        Vector3D m = (2 * (s.dot(n)) * n) - s;
        m.normalize();

        Colour ambient = r_a * I_a;
        Colour diffuse = std::max(n.dot(s), 0.0) * r_d * I_d;
        Colour specular = pow(std::max(0.0, c.dot(m)), alpha) * r_s * I_s; 

        ray.col = ambient
        	+ diffuse
        	+ specular;

        ray.col.clamp();
        
    }
}

/*  This is really bad right now and was a hack when first put together. 
 *  Need to rethink area light sources
 */
void AreaLight::shade( Ray3D& ray ) {
    
    Colour I_a = _col_ambient;
    Colour I_d = _col_diffuse;
    Colour I_s = _col_specular;

    Colour r_a = ray.intersection.mat->ambient;
    Colour r_d = ray.intersection.mat->diffuse;
    Colour r_s = ray.intersection.mat->specular;
    double alpha = ray.intersection.mat->specular_exp;

    for(int i = 0; i < 4; i++){
        Vector3D view = Vector3D(ray.origin - ray.intersection.point);

        Vector3D n = ray.intersection.normal;
        n.normalize();

        int factor = 1;

        Vector3D s = Vector3D((get_position() + Vector3D(i * factor, i * factor, i *factor)) - ray.intersection.point);
        s.normalize();

        Vector3D c = -ray.dir;
        c.normalize();

        Vector3D m = (2 * (s.dot(n)) * n) - s;
        m.normalize();

        Colour ambient = r_a * I_a;
        Colour diffuse = std::max(n.dot(s), 0.0) * r_d * I_d;
        Colour specular = pow(std::max(0.0, c.dot(m)), alpha) * r_s * I_s; 

        ray.col = ray.col + ambient
            + diffuse
            + specular;
    }

    ray.col = 0.25 * ray.col;

    ray.col.clamp();

}