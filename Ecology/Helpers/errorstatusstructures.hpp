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
    MAX = SaveError,
};

enum class ReadingState : unsigned char
{
    MIN,
    Ok = MIN,
    FileCorrupted,
    ConvertionFailed,
    NotEnoughData,
    MAX = NotEnoughData,
};

enum class WrittingState : unsigned char
{
    MIN,
    Ok = MIN,
    FileNotExist,
    Undefined,
    WrittingError,
    FileNotSaved,
    FileCorrupted,
    MAX = FileCorrupted,
};

#endif // ERRORSTATUSSTRUCTURES_H
