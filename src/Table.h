#ifndef table_h
#define table_h

#include "Storable.cpp"
#include "Error.cpp"

#include <vector>
#include <string>
#include <fstream>

template <class T>
class Table {
private:
	std::string fileName;
	std::fstream fileStream;
	std::vector<Storable *> *records = NULL;

	T * getReferenceOfRecordForId(long recordId) const throw(NoSuchRecordError) {
		for (Storable* s : *records) {
			T* ref = static_cast<T*>(s);
			if (ref->recordId == recordId) return ref;
		}
		throw NoSuchRecordError();
	}

	void writeToFile() throw(IOError) {
		this->fileStream.open(fileName.c_str(), std::ios::out | std::ios::trunc);
		if (!fileStream) throw IOError();

		for (auto & record : *records) {
			fileStream << record->toString() << std::endl;
		}
		this->fileStream.close();
	}

	const T* const addNewRecord(T data) throw(MemoryError, IOError) {
		T* record = new T(data);
		if (!record) throw MemoryError();

		record->recordId = getNextRecordId();
		records->push_back(record);

		try {
			writeToFile();
		}
		catch (IOError &e) {
			records->pop_back();
			delete record;
			throw;
		}

		return record;
	}

	void updateRecord(T updatedRecord) throw(IOError, NoSuchRecordError) {
		T* originalRecord = getReferenceOfRecordForId(updatedRecord.recordId);
		*originalRecord = updatedRecord;
		writeToFile();
	}

public:
	Table(std::string fileName) throw(MemoryError) {
		this->fileName = fileName;
		this->records = new std::vector<Storable *>();
		if (!this->records) throw MemoryError();
	}

	~Table() {
		for (Storable* s : *records) {
			delete s;
		}
		delete records;
	}

	long getNextRecordId() const {
		return records->size() + 1;
	}

	const T* const getRecordForId(long recordId) const throw(NoSuchRecordError) {
		for (Storable* s : *records) {
			T* r = static_cast<T*>(s);
			if (r->recordId == recordId) return r;
		}
		throw NoSuchRecordError();
	}

	friend class Database;
};

#endif
