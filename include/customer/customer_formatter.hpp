#pragma once
#include <memory>
#include <string>
#include "customer/customer_archive.hpp"

namespace customer 
{
    class CustomerFormatter 
    {
    public:
        explicit CustomerFormatter(std::shared_ptr<const ICustomerArchiveReader> archive_reader);
        std::string formatById(int id) const;
    private:
        std::shared_ptr<const ICustomerArchiveReader> archive_reader_;
    };
}
