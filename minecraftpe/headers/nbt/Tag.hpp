#pragma once
#include <_types.h>
#include <string>

struct IDataInput;
struct IDataOutput;
struct PrintStream;

struct Tag{
	int32_t field_0;
	std::string tagName; //TODO probably wrong type

	static std::string NullString;

	Tag(const std::string&);

	virtual ~Tag(void);
	virtual	void deleteChildren(void);
	virtual void write(IDataOutput*) = 0;
	virtual void load(IDataInput*) = 0;
	virtual std::string	toString(void) = 0;
	virtual int32_t getId(void) const = 0;
	bool_t equals(const Tag&);
	virtual void print(PrintStream&);
	virtual	void print(const std::string&, PrintStream&);
	virtual	void setName(const std::string&);
	virtual	std::string getName(void) const;
	virtual Tag* copy(void) = 0;

	static void writeNamedTag(Tag*, IDataOutput*);
	static Tag* readNamedTag(IDataInput*);
	static std::string getTagName(char);
	static Tag* newTag(char, const std::string&);
};
