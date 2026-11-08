#pragma once
#include <_types.h>
#include <string>
#include <_PrintStream.hpp>

struct IDataInput;
struct IDataOutput;

struct Tag{
	int32_t err;
	std::string tagName;

	static std::string NullString;

	Tag(const std::string&);

	virtual ~Tag(void){}
	virtual	void deleteChildren(void){}
	virtual void write(IDataOutput*) = 0;
	virtual void load(IDataInput*) = 0;
	virtual std::string	toString(void) const = 0;
	virtual char getId(void) const = 0;
	virtual bool_t equals(const Tag&) const;
	virtual void print(PrintStream&) const;
	virtual	void print(const std::string&, PrintStream&) const;
	virtual	Tag* setName(const std::string&);
	virtual	std::string getName(void) const;
	virtual Tag* copy(void) const = 0;

	static void writeNamedTag(Tag*, IDataOutput*);
	static Tag* readNamedTag(IDataInput*);
	static std::string getTagName(char);
	static Tag* newTag(char, const std::string&);
};
