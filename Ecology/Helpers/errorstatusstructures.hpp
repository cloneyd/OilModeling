#ifndef ERRORSTATUSSTRUCTURES_H
#define ERRORSTATUSSTRUCTURES_H

enum class SaveOperationStatus
{
    MIN,
    Ok = MIN,
    FilepathError,
    ObjectError, // means that save object is corrupted
    FatalObjectError, // means that app must be reload
    SaveError, // if problem cannot be detected
    MAX = SaveError
};

#endif // ERRORSTATUSSTRUCTURES_H
