import Geometry;
//test that the shit is actually a type
//test ray.at
//

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <type_traits>

template<Numerical T>
class Rand_number {
	public:
        Rand_number() {}
        Rand_number(double low, double high) : dist_f{low,high} {}
        Rand_number(int low, int high) : dist_i{low,high} {}

	Numerical auto operator()() {
            if constexpr (std::is_integral_v<T>){
                return dist_i(re); 
            }
            else{
                return dist_f(re); 
            }
        }
	void seed(Numerical auto s) { re.seed(s); }
	private:
            std::default_random_engine re;
            std::uniform_int_distribution<> dist_i;
            std::uniform_real_distribution<> dist_f;
};

class GeometryTest : public testing::Test {
    protected:
        Rand_number<float> random_float;
        Rand_number<int> random_int;
        
        Point_3d<float> random_point_f;
        Vector_3d<float> random_velocity_f;
        Ray<float> random_ray_f;
        
        Point_3d<int> random_point_i;
        Vector_3d<int> random_velocity_i;
        Ray<int> random_ray_i;

        GeometryTest()
        {  
            random_int = Rand_number<int>(0, 300);
            random_float = Rand_number<float>(0, 300);
            for(int i = 0; i < 3; i++){
                random_point_f[i] = random_float();
            }
            for(int i = 0; i < 3; i++){
                random_velocity_f[i] = random_float();
            }
            random_ray_f = Ray<float>{.origin = random_point_f, .velocity = random_velocity_f};
            for(int i = 0; i < 3; i++){
                random_point_i[i] = random_int();
            }
            for(int i = 0; i < 3; i++){
                random_velocity_i[i] = random_int();
            }
            random_ray_i = Ray<int>{.origin = random_point_i, .velocity = random_velocity_i};
        }
        
        ~GeometryTest() {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // Class members declared here can be used by all tests in the test suite
        // for Foo.
};

TEST_F(GeometryTest, ray_at_works) {
    double t = random_float();
    Point_3d<float> expected_point_f;
    Point_3d<int> expected_point_i;
    for(int i = 0; i < 3; i++){
        expected_point_f[i] = random_ray_f.origin[i] + random_ray_f.velocity[i] * t;
    }
    for(int i = 0; i < 3; i++){
        EXPECT_EQ(random_ray_f.at(t)[i], expected_point_f[i]) << i << "th Coordinate's Value: " << random_ray_f.at(t)[i] << " Expected Value: " << expected_point_f[i] << std::endl;
    }
    for(int i = 0; i < 3; i++){
        expected_point_i[i] = random_ray_i.origin[i] + random_ray_i.velocity[i] * t;
    }
    for(int i = 0; i < 3; i++){
        EXPECT_EQ(random_ray_i.at(t)[i], expected_point_i[i]) << i << "th Coordinate's Value: " << random_ray_i.at(t)[i] << " Expected Value: " << expected_point_i[i] << std::endl;
    }
}
