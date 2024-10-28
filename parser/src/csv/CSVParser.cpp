#include "CSVParser.hpp"

jpl::_parser::_csv::CSVParser::CSVParser() : jpl::_parser::_csv::CSVParser(";") {}
jpl::_parser::_csv::CSVParser::CSVParser(const char* separator) : separator(separator){
    if(separator == nullptr){
        throw jpl::_exception::IllegalArgumentException("Char separator is nullptr");
    }
    this->multiTable = false;
    this->size = 0;
}


void jpl::_parser::_csv::CSVParser::addTable(jpl::_utils::_collections::Table* table){
    if(table == nullptr)
        throw jpl::_exception::IllegalArgumentException("You cannot add a nullptr");
    if(!this->multiTable && !this->tables.isEmpty())
        throw jpl::_exception::IllegalStateException("This CSV Parser already contains a table instance. If you wanna insert another one, you have to enable multi-table mode before");
    for(size_t i = 0; i < this->tables.getSize(); i++){
        jpl::_utils::_collections::Table* cr = this->tables.get(i);
        if(cr == table)
            throw jpl::_exception::RuntimeException("This table has been already inserted");
        if(cr->getName().compare(table->getName()) == 0)
            throw jpl::_exception::RuntimeException("There's already a table named as " + table->getName());
    }
    this->tables.add(table);
}


void jpl::_parser::_csv::CSVParser::parse(std::istream* is){
    std::string buffer;
    std::string line;
    while(std::getline(*is, line)){
        if(line.empty()){
            break;  //In multi table mode, the empty line marks separation between header and data
        }else{
            buffer += line + "\n";
        }
        if(!this->multiTable){
            break;  //In standard mode, there could not be any separation-empty-line
        }
    }
    this->parseHeader(buffer);
    this->parseData(is);
}


void jpl::_parser::_csv::CSVParser::parseHeader(const std::string &header){
    size_t i = 0, j;    //i -> table; j -> column
    bool check = !this->tables.isEmpty();   // (1)
    std::istringstream iss = std::istringstream(header);
    std::string tableDecl;
    size_t endSingleCol;
    while(std::getline(iss, tableDecl)){
        if(tableDecl.empty())
            continue;
        j = 0;
        jpl::_utils::_collections::Table* table;
        if(check){
            if(this->tables.getSize() <= i){    //Check if there are at least i-1 tables
                throw jpl::_exception::RuntimeException("There are only " + std::to_string(this->tables.getSize()) + " declared tables into list");
            }
            table = this->tables.get(i++);
        }else{
            table = new jpl::_utils::_collections::Table(std::to_string(i++), true, true);    //Instance i-th table 
        }
        while ( (endSingleCol = tableDecl.find(this->separator) ) != std::string::npos){   //Each column
            std::string colName = tableDecl.substr(0, endSingleCol);
            if(colName.empty()){
                throw jpl::_parser::_csv::_exception::CSVParsingException("There's an empty column name for the " + std::to_string(i) + " table");
            }
            tableDecl.erase(0, endSingleCol+1);
            if(check){
                if(table->getColumnsSize() <= j){
                    throw jpl::_exception::RuntimeException("Table " + table->getName() + " has only " + std::to_string(table->getColumnsSize()) + " columns");
                }
                if(table->getColumn(j)->getName().compare(colName) != 0){
                    throw jpl::_parser::_csv::_exception::CSVParsingException("Table " + table->getName() + " does not contain " + colName + " column");
                }
            }else{
                table->addColumn(new jpl::_utils::_collections::Column<std::string>(colName, false));
            }
            j++;
        }
        if(!check){
            this->tables.add(table);
        }
        if(i == 0 && !this->multiTable){
            break;
        }
    }
}

void jpl::_parser::_csv::CSVParser::parseData(std::istream* is){
    if(is == nullptr){
        throw jpl::_exception::IllegalArgumentException("input stream passed is nullptr");
    }
    std::string line;
    size_t i = 0;
    jpl::_utils::_collections::Table* table = this->tables.get(i);
    while(std::getline(*is, line)){
        if(this->multiTable){
            if(line.empty()){
                if(i != this->tables.getSize() && i != 0){
                    this->checkMissingMandatoryColumnsPerTables(i);
                }
                i = 0;
                continue;
            }else{
                if(i+1 > this->tables.getSize())
                    throw jpl::_parser::_csv::_exception::CSVParsingException("There's a set of data of " + std::to_string(i+1) + " rows. Max is " + std::to_string(this->tables.getSize()));
                if(i == 0)  //it is beginning a new tuples cluster
                    this->size++;
                table = this->tables.get(i++);
            }
        }else{
            this->size++;   //Each row, in single-table mode, is a cluster
        }
        size_t endValue;
        jpl::_utils::_collections::_list::ArrayList<std::string>* values = new jpl::_utils::_collections::_list::ArrayList<std::string>(table->getColumnsSize());
        jpl::_utils::_collections::Tuple* tuple = new jpl::_utils::_collections::Tuple(table->getTuplesSize(), values);
        table->addTuple(tuple);
        size_t j = 0;
        bool flag = true;
        do{
            endValue = line.find(this->separator);
            if(endValue == std::string::npos){
                flag = false;
                endValue = line.size();
            }
            std::string value = line.substr(0, endValue);
            if(flag){
                line = line.erase(0, endValue+1);
            }
            if(value.empty()){//Empty value, it checks if column is mandatory
                jpl::_utils::_collections::AbstractColumn* col = table->getColumn(j);
                if(col->isMandatory()){
                    throw jpl::_parser::_csv::_exception::CSVParsingException(col->getName() + " column is mandatory");
                }
            }
            jpl::_utils::_collections::TableWrapper::setSmartValue(table, table->getTuplesSize()-1, j++, value);
        }while(flag);
        if(j != table->getColumnsSize()){   //Once line is completely parsed, it checks if there are any missing mandatory columns
            this->checkMissingMandatoryColumns(table, j);
        }
    }
    if(this->multiTable){
        if(i != this->tables.getSize() && i != 0){//If a single cluster of table
            this->checkMissingMandatoryColumnsPerTables(i);
        }
    }
}

jpl::_parser::_csv::CSVParser::~CSVParser(){
    this->tables.clear();
}

void jpl::_parser::_csv::CSVParser::checkMissingMandatoryColumnsPerTables(size_t iStart) const{
    if(iStart >= this->tables.getSize())
        throw jpl::_exception::IndexOutOfBoundsException(tables.getSize(), iStart);
    for(size_t i = iStart; i < this->tables.getSize(); i++){
        jpl::_utils::_collections::Table* cr = this->tables.get(i);
        this->checkMissingMandatoryColumns(cr, 0);
    }
}

void jpl::_parser::_csv::CSVParser::checkMissingMandatoryColumns(jpl::_utils::_collections::Table* table, size_t iStart) const{
    if(table == nullptr)
        throw jpl::_exception::IllegalArgumentException("Checking Missing Mandatory Columns on a nullptr table");
    if(iStart >= table->getColumnsSize())
        throw jpl::_exception::IndexOutOfBoundsException(table->getColumnsSize(), iStart);
    for(size_t i = iStart; i < table->getColumnsSize(); i++){
        jpl::_utils::_collections::AbstractColumn* cr = table->getColumn(i);
        if(cr->isMandatory()){
            throw jpl::_parser::_csv::_exception::CSVParsingException(cr->getName() + " column of " + table->getName() + " table is mandatory");
        }
    }
}

void jpl::_parser::_csv::CSVParser::write(std::ostream* os, const jpl::_parser::_csv::CSVParser* const csv){
    if(os == nullptr)
        throw jpl::_exception::IllegalArgumentException("Attempting to write csv on a nullptr ostream");
    if(csv == nullptr)
        throw jpl::_exception::IllegalArgumentException("Attempting to write a nullptr csv");   
    for (size_t i = 0; i < csv->tables.getSize(); i++){
        jpl::_utils::_collections::Table* cr = csv->tables.get(i);
        for(size_t j = 0; j < cr->getColumnsSize(); j++){
            jpl::_utils::_collections::AbstractColumn* col = cr->getColumn(j);
            std::string colName = col->getName();
            os->write(colName.c_str(), colName.size());
            if(j < cr->getColumnsSize()-1){
                os->write(csv->separator, 1);
            }
        }
        os->write("\n", 1);
    }
    if(csv->multiTable)
        os->write("\n", 1);
    jpl::_utils::_collections::Table* table = csv->tables.get(0);
    size_t colSize = table->getColumnsSize();
    for (size_t i = 0; i < csv->size; i++){
        for(size_t j = 0; j < csv->tables.getSize();){
            const jpl::_utils::_collections::Tuple* const tuple = table->getTuple(i);
            for(size_t l = 0; l < colSize; l++){
                std::string value = tuple->getValue(l);
                os->write(value.c_str(), value.size());
                if(l < colSize-1){
                    os->write(csv->separator, 1);
                }
            }
            j++;
            if(csv->multiTable){
                if(j == csv->tables.getSize())
                    table = csv->tables.get(0);
                else
                    table = csv->tables.get(j);
                colSize = table->getColumnsSize();
                os->write("\n", 1);
            }
        }
        os->write("\n", 1);
    }
}