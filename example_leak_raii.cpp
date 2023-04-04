#include <resources/kernel_resource.h>

#include <iostream>
#include <vector>

#include <memory> // std::unique_ptr

using Event = int;

std::unique_ptr<Event> create_event(int event_id) noexcept{return std::unique_ptr<Event>(new Event(event_id));}

void process_init(RESOURCE* resource) noexcept
try {
    if (resource) {
        use_resource(resource);
        free_resource(resource);
    }
} catch (std::runtime_error const& ex) {
    std::cout << ex.what() << std::endl;
}

void process_event(std::unique_ptr<Event> &event,
                   std::unique_ptr<RESOURCE> &temp_resource,
                   RESOURCE* proc_resource) noexcept
{
try {
    std::cout << "Processing Event(" << *event << ")" << std::endl;

    if (temp_resource) {
        use_resource(temp_resource.get());
        free_resource(temp_resource.get());
    }

    if (proc_resource) {
        use_resource(proc_resource);
    }

} catch (std::runtime_error const& ex) {
    std::cout << ex.what() << std::endl;
}
}
int main(int ac, char* av[])
{
    auto init_resource = allocate_resource();
    process_init(init_resource);

    auto proc_resource = allocate_resource();

    std::vector<int> simulation = {
        12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144};
    for (auto id : simulation) {
        std::unique_ptr <Event> event = std::move(create_event(id));
        std::unique_ptr<RESOURCE, free_resource()> temp_resource;
        //auto temp_resource = allocate_resource();
        process_event(event, temp_resource, proc_resource);
    }

    if (proc_resource) {
        free_resource(proc_resource);
    }

    return 0;
}
