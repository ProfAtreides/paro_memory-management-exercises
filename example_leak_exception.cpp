#include <resources/kernel_resource.h>
#include <iostream>
#include <stdexcept> // std::runtime_error

void kernel_stress_test()
{
    // will return NULL if:
    // 1. allocation was not successful
    // will THROW std::runtime_error if:
    // 1. sometimes, due to internal reasons (wrap in try-catch!)
    RESOURCE* resource;
    try
    {
    resource = allocate_resource();
        if(not resource) return;
    }
    catch (std::runtime_error&)
    {
        throw;
    }

    // use_resource
    // will THROW std::runtime_error if:
    // 1. sometimes, with no particular reason (wrap in try-catch!)
    // will CRASH (std::terminate) if:
    // 1. resource is NULL (add NULL-check!)
    // 2. resource was already released
    try
    {
        use_resource(resource);
        try
        {
           // std::cout <<"REMOVING RESOURCE"<<std::endl;
            free_resource(resource);
        }
        catch (std::runtime_error& kernel_operation_error)
        {;
            throw;
        }
    }
    catch (std::runtime_error& kernel_operation_error)
    {;
        try
        {
           // std::cout <<"REMOVING RESOURCE"<<std::endl;
            free_resource(resource);
        }
        catch (std::runtime_error& kernel_operation_error)
        {;
            throw;
        }
    }
    // free_resource
    // will CRASH (std::terminate) if:
    // 1. resource is NULL (add NULL-check!)
    // 2. resource is already released
}

int main(int ac, char* av[])
{
    constexpr int repetitions = 32;

    for (int i = 0; i < repetitions; ++i) { kernel_stress_test(); }

    // the program will CRASH (std::terminate) if:
    // 1. there are resources not yet released on exit

    return 0;
}
