//
// Created by michal on 4/19/20.
//

#ifndef SEMESTRAL_WORK_SERIALIZABLE_H
#define SEMESTRAL_WORK_SERIALIZABLE_H

#include <iostream>

/**
 * Interface that is meant to be implemented by objects
 * needing serialization and deserialization
 */
class Serializable {

    /**
     * @brief Serialize itself to stream
     * @param os    Output stream to write to
     */
    virtual void serialize(std::ostream &os) const = 0;

    /**
     * @brief Deserialize itself from stream (load data)
     * @param is    Input stream to read from
     */
    virtual void deserialize(std::istream &is) = 0;
};


#endif //SEMESTRAL_WORK_SERIALIZABLE_H
