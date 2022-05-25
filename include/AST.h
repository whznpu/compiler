#pragma once
#include<iostream>
#include<sstream>



class BaseAST {
 public:
 static std::stringstream ss;

  	virtual ~BaseAST() = default;

  	virtual void Dump() const = 0;
};

class CompUnitAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_def;

  void Dump() const override {
//     ss << "CompUnitAST { ";
    func_def->Dump();
//     ss << " }";
  }
};

class FuncDefAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;

  void Dump() const override {
	  ss<<"fun @";
	  ss<<ident<<"(): ";
	  func_type->Dump();
//     ss << "FuncDefAST { ";
//     func_type->Dump();
//     ss << ", " << ident << ", ";
    block->Dump();
//     ss << " }";
  }
};

class FuncTypeAST : public BaseAST {
	public:
	void Dump() const override {
		// ss<<"FuncTypeAST { int }";
		ss<<"i32 ";
	}
};

class BlockAST : public BaseAST{
	public:
	std::unique_ptr<BaseAST> stmt;
	void Dump() const override{
		// ss<<"BlockAST { ";
		ss<<"{"<<std::endl;
		ss<<"%entry:"<<std::endl;
		stmt->Dump();
		ss<<"}"<<std::endl;

	}

};

class StmtAST : public BaseAST{
	public:
	std::string number;
	void Dump() const override{
		ss<<"  ret ";
		ss<<number<<std::endl;
	}
};



// ...
