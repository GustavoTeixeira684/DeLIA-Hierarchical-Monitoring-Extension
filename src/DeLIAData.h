#ifndef DELIADATA_H_
#define DELIADATA_H_

#define NO_CODE     0
#define INT_CODE    1
#define DOUBLE_CODE 2
#define CHAR_CODE   3
#define FLOAT_CODE  4
#define BOOL_CODE   5

/**
 * @brief Node of the list of data that
 * it will be save by the library.
 * If the application does not pass IDataGlobal and/or IDataLocal, this struct is used
 */
struct DeLIAData {
    void *data; /*!< Data*/
    int sizeOfData; /*!< size of the data*/
    int typeCode; /*!< type of the data from the next node*/
} ;

#endif