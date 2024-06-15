#pragma once


#include <complexities/complexity_analyzer.h>
#include <list>
#include <random>
#include <vector>

#include "libds/adt/table.h"

namespace ds::utils
{
    template<typename Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void growToSize(Table& structure, size_t size) override;
        size_t getRandomKey() const;
        int getRandomData() const;

    private:
        std::default_random_engine rngData_;
        std::default_random_engine rngKey_;
        size_t key_;
        int data_;
    };

    template <typename Table>
    TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name),
        rngData_(144),
        rngKey_(144),
        key_(0),
        data_(0)
    {

        ComplexityAnalyzer<Table>::registerBeforeOperation([this](Table& table)
            {
                while (table.contains(key_))
                {
                    key_ = rngKey_();
                }

                data_ = rngData_();
            });

    }

    template <typename Table>
    void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
    {

    }

    template <typename Table>
    size_t TableAnalyzer<Table>::getRandomKey() const
    {
        return key_;
    }

    template <typename Table>
    int TableAnalyzer<Table>::getRandomData() const
    {
        return data_;
    }

    template<typename Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);


    protected:
        void executeOperation(Table& structure) override;
    };

    template <typename Table>
    TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {
    }

    template <typename Table>
    void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
    {
            structure.insert(this->getRandomKey(), this->getRandomData());

       
    }

    template<typename Table>
    class TableFindAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
        void growToSize(Table& structure, size_t size) override;
    };

    template <typename Table>
    TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {

    }

    template <typename Table>
    void TableFindAnalyzer<Table>::executeOperation(Table& structure)
    {
        int* data = nullptr;
        structure.tryFind(this->getRandomKey(), data);
    }


    template <typename Table>
    void TableFindAnalyzer<Table>::growToSize(Table& structure, size_t size)
    {
        size_t howMany = size - structure.size();
        
        for (size_t i = 0; i < howMany; ++i) {
            try {
                structure.insert(this->getRandomKey(), this->getRandomData());
            }
            catch (std::exception e) {
                
            }
           
        }
    }


    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer();
    };


    inline TablesAnalyzer::TablesAnalyzer() :
        CompositeAnalyzer("Tables")
    {

        this->addAnalyzer(std::make_unique < TableInsertAnalyzer<ds::adt::GeneralBinarySearchTree<int, int, ds::adt::TableItem<int, int>>>>("table-insert"));
        this->addAnalyzer(std::make_unique < TableFindAnalyzer<ds::adt::GeneralBinarySearchTree<int, int, ds::adt::TableItem<int, int>>>>("table-find"));

    }
};