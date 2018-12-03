#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/util/lightweight_test.hpp>
#include <hpx/include/parallel_for_loop.hpp>
#include <hpx/include/parallel_executor_parameters.hpp>
#include <numeric>


int hpx_main(boost::program_options::variables_map& vm)
{
    using hpx::parallel::for_loop;
    using hpx::parallel::execution::par;

    std::size_t vector_size = vm["vec_size"].as<std::size_t>();

    using hpx::parallel::for_loop;
    using hpx::parallel::execution::par;

    std::vector<float> a(vector_size,2.0f);
    std::vector<float> b(vector_size,3.0f);
    std::vector<float> c(vector_size,0);

    auto start = std::chrono::system_clock::now();

    for_loop(size_t(0), vector_size, [&](int i) {
        c[i] = a[i] + b[i];
    });
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    double elapsed_secs = elapsed_seconds.count();

    std::cout<<"time(seconds): "<<elapsed_secs<<std::endl;

    float operations = vector_size*1/elapsed_secs/1000000;

    for (int64_t i = 0; i < vector_size; i++){
        if(c[i] != 5){
            std::cout<<",WRONG ANSWER,"<<std::endl;
            throw std::invalid_argument("wrong result");
        }
    }

    std::cout<<"MFLOPS: "<<operations<<std::endl;

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;

    po::options_description desc_commandline;
    desc_commandline.add_options()
            ("vec_size", po::value<std::size_t>()->default_value(10000),"vector size")
            ;

    // Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}