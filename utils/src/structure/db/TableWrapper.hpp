/**
 * @file
 * 
 * The Table Wrapper add a layer upon the table about getting and setting values from/into tuple.
 * 
 * The setting-of-value is done after have checked if table allows tuple-editing
 * 
 * @author Gabriele-P03
 */
#ifndef TABLE_WRAPPER_JPL
#define TABLE_WRAPPER_JPL

#include "Table.hpp"
#include "columns/Column.hpp"

namespace jpl{
    namespace _utils{
        namespace _collections{

            class TableWrapper{

                public:

                    /*********************************************************
                     *  STRING
                     ********************************************************/

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<std::string> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the string value of colName column of tuple at iTuple position of the given table
                     */
                    static std::string getStringValue(Table* table, size_t iTuple, std::string colName);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param iCol index of the column
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<std::string> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the string value of colName column of tuple at iTuple position of the given table
                     */
                    static std::string getStringValue(Table* table, size_t iTuple, size_t iCol);

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<std::string> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     * @throw IllegalArgumentException if value is an empty string and column does not allow it
                     */
                    static void setStringValue(Table* table, size_t iTuple, std::string colName, std::string value);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<std::string> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     * @throw IllegalArgumentException if value is an empty string and column does not allow it
                     */
                    static void setStringValue(Table* table, size_t iTuple, size_t iCol, std::string value);




                    /*********************************************************
                     *  BOOLEAN
                     ********************************************************/

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<bool> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the boolean value of colName column of tuple at iTuple position of the given table
                     */
                    static bool getBoolValue(Table* table, size_t iTuple, std::string colName);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param iCol index of the column
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<bool> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the boolean value of colName column of tuple at iTuple position of the given table
                     */
                    static bool getBoolValue(Table* table, size_t iTuple, size_t iCol);

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<bool> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setBoolValue(Table* table, size_t iTuple, std::string colName, bool value);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<bool> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setBoolValue(Table* table, size_t iTuple, size_t iCol, bool value);


                    /*********************************************************
                     *  DOUBLE
                     ********************************************************/

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<double> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the double value of colName column of tuple at iTuple position of the given table
                     */
                    static double getDoubleValue(Table* table, size_t iTuple, std::string colName);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param iCol index of the column
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<double> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the double value of colName column of tuple at iTuple position of the given table
                     */
                    static double getDoubleValue(Table* table, size_t iTuple, size_t iCol);

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<double> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setDoubleValue(Table* table, size_t iTuple, std::string colName, double value);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<double> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setDoubleValue(Table* table, size_t iTuple, size_t iCol, double value);


                    /*********************************************************
                     *  LONG
                     ********************************************************/

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<long> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the long value of colName column of tuple at iTuple position of the given table
                     */
                    static long getLongValue(Table* table, size_t iTuple, std::string colName);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param iCol index of the column
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<long> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the long value of colName column of tuple at iTuple position of the given table
                     */
                    static long getLongValue(Table* table, size_t iTuple, size_t iCol);

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<long> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setLongValue(Table* table, size_t iTuple, std::string colName, long value);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<long> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setLongValue(Table* table, size_t iTuple, size_t iCol, long value);



                    /*********************************************************
                     *  INT
                     ********************************************************/

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<int> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the int value of colName column of tuple at iTuple position of the given table
                     */
                    static int getIntValue(Table* table, size_t iTuple, std::string colName);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param iCol index of the column
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<int> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the int value of colName column of tuple at iTuple position of the given table
                     */
                    static int getIntValue(Table* table, size_t iTuple, size_t iCol);

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<int> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setIntValue(Table* table, size_t iTuple, std::string colName, int value);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<int> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setIntValue(Table* table, size_t iTuple, size_t iCol, int value);



                    /*********************************************************
                     *  CHAR*
                     ********************************************************/

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<const char*> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the const char* value of colName column of tuple at iTuple position of the given table
                     */
                    static const char* getCharsValue(Table* table, size_t iTuple, std::string colName);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param iCol index of the column
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<const char*> 
                     * @throw IllegalArgumentException if table is nullptr
                     * 
                     * @return the const char* value of colName column of tuple at iTuple position of the given table
                     */
                    static const char* getCharsValue(Table* table, size_t iTuple, size_t iCol);

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<const char*> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setCharsValue(Table* table, size_t iTuple, std::string colName, const char* value);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<const char*> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     */
                    static void setCharsValue(Table* table, size_t iTuple, size_t iCol, const char* value);


                    /*********************************************************
                     *  SMART -> Algorithm chooses what kind of column is required.
                     *  
                     *  Value must be passed as std::string in order to guarantee compatiblity 
                     ********************************************************/

                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw NotFoundException if table's columns list does not contains any column called as colName
                     * @throw RuntimeException if colName column is not an instance of Column<std::string> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     * @throw IllegalArgumentException if value is an empty string and column does not allow it
                     */
                    static void setSmartValue(Table* table, size_t iTuple, std::string colName, std::string value);
                    /**
                     * @param table
                     * @param iTuple index of the tuple 
                     * @param colName column's name
                     * @param value
                     * 
                     * @throw IndexOutOfBounds if iTuple is greater or equals than table's tuples' size
                     * @throw IndexOutOfBounds if iCol is greater or equals than table's columns' size
                     * @throw RuntimeException if colName column is not an instance of Column<std::string> 
                     * @throw IllegalArgumentException if table is nullptr
                     * @throw IllegalStateException if table does not allow to edit tuple
                     * @throw IllegalArgumentException if value is an empty string and column does not allow it
                     */
                    static void setSmartValue(Table* table, size_t iTuple, size_t iCol, std::string value);
            };
        }
    }
}

#endif