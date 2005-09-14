#ifndef DDPartSelection_h
#define DDPartSelection_h

#include <vector>
#include <string>
#include <iostream>
#include "DetectorDescription/Core/interface/DDLogicalPart.h"

#include <boost/spirit.hpp>


class DDLogicalPart;

enum ddselection_type { ddunknown,   //   ->    (should never appear!)
                        ddanynode,   //   ->    //*
	                ddanychild,  //   ->    /*
	                ddanylogp,   //   ->    //NameOfLogicalPart
	                ddanyposp,   //   ->    //NameOfLogicalPart[copyno]
	                ddchildlogp, //   ->    /NameOfLogicalPart
	                ddchildposp  //   ->    /NameOfLogicalPart[copyno]
	               };

//typedef DDRedirect<DDLogicalPartImpl> lpredir_type; // logical-part-redirection_type

struct DDPartSelRegExpLevel
{
  DDPartSelRegExpLevel(const std::string & ns, const std::string & nm, int cpn, ddselection_type t, bool isRegex=false)
  : ns_(ns), nm_(nm), copyno_(cpn), selectionType_(t), isRegex_(isRegex) { }
  std::string ns_, nm_;
  int copyno_;
  ddselection_type selectionType_;
  bool isRegex_;
};


struct DDPartSelectionLevel
{
  DDPartSelectionLevel(const DDLogicalPart &, int, ddselection_type);
  DDLogicalPart lp_;
  int copyno_;
  ddselection_type selectionType_;
};


class DDPartSelection : public std::vector<DDPartSelectionLevel>
{
public:
  DDPartSelection() : std::vector<DDPartSelectionLevel>() { }
};
/*
class DDPartSelection : public std::vector<DDPartSelectionLevel>
{
public:
  DDPartSelection() { }; // to use it in stl-containers
  DDPartSelection(const std::string & selectionString);
  
  ~DDPartSelection() { }
  
};
*/


std::ostream & operator<<(std::ostream &, const DDPartSelection &);
std::ostream & operator<<(std::ostream &, const std::vector<DDPartSelection> &);

void DDTokenize2(const std::string & selectionString, std::vector<DDPartSelRegExpLevel> & result);
void DDTokenize(const std::string & selectionString, std::vector<DDPartSelRegExpLevel> & result);
std::ostream & operator<<(std::ostream &, const DDPartSelection &);

#endif
