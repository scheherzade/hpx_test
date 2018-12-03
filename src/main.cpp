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

    std::size_t n = vm["vec_size"].as<std::size_t>();
    std::size_t chunk_size = vm["chunk_size"].as<std::size_t>();
    bool static_scheduling=vm.count("static")!=0;

    std::vector<double> x(n,1);
    std::vector<double> y(n,1);
    double a=3.0;

    if (!static_scheduling)
    {
        hpx::parallel::execution::dynamic_chunk_size ds(chunk_size);
        std::uint64_t t = hpx::util::high_resolution_clock::now();
        for_loop( par.with(ds), size_t(0), n,[&](int i)
        {
            y[i] += a * x[i];
        });
        std::uint64_t elapsed = hpx::util::high_resolution_clock::now() - t;
        std::cout<<"Dynamic scheduling: vector size:   "<<n<<"   chunk size: "<<chunk_size<<"   time(ns): "<<elapsed*1e-9<<std::endl;
    }
    else
    {
        hpx::parallel::execution::static_chunk_size s;
        std::uint64_t t = hpx::util::high_resolution_clock::now();
        for_loop(par.with(s), size_t(0), n, [&](int i) {
            y[i] += a * x[i];
        });
        std::uint64_t elapsed = hpx::util::high_resolution_clock::now() - t;
        std::cout << "Static scheduling: vector size:   " << n << "   time(ns): " << elapsed * 1e-9 << std::endl;
    }

    double sum_of_elems = std::accumulate(y.begin(), y.end(), 0);
    HPX_TEST_EQ(sum_of_elems, 4*n);

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;

    po::options_description desc_commandline;
    desc_commandline.add_options()
            ("vec_size", po::value<std::size_t>()->default_value(10000),"vector size")
            ("chunk_size", po::value<std::size_t>()->default_value(1),"chunk size")
            ("static", "static scheduling")
            ;

    // Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}
