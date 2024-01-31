#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <variant>


using namespace std;

// basic class for AST

class BaseAST {
		public:
				virtual ~BaseAST() = default;
				virtual void Dump() const = 0;
				virtual std::string dumpIR() const = 0;
};

class CompUnitAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> func_def;

				void Dump() const override {
					std::cout << "CompUnitAST { ";
					func_def->Dump();
					std::cout << " } ";
				  }

				std::string dumpIR() const override {
						func_def->dumpIR();	
						return "";
				}
};

class FuncDefAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> func_type;
				std::string ident;
				std::unique_ptr<BaseAST> block;
				
				void Dump() const override {
					std::cout << "FuncDefAST { ";
					func_type->Dump();
					std::cout << ", " << ident << ", ";
					block->Dump();
					std::cout << " } ";
				  }

				std::string dumpIR() const override {
					// generate fun @IDENT()_
					std::string func_name = "@" + ident;
					std::cout << "fun " << func_name << "()";

					// generate the func_type's IR, the dumpIR() function will return the type
					// like i32 or some else
					std::string current_func_type = func_type->dumpIR();
					if (current_func_type == "int") {
							std::cout << ": i32";
							//func_type->dumpIR();
					}
				 	else if (current_func_type != "void") {
							assert(false);
					}

					// generate the middle part
					// like {\n %entry:\n
					std::cout << " {" << std::endl << "\%entry_" << ident << ":" << std::endl;

					// generate the block's IR like ret 0 or some else
					std::string block_type = block->dumpIR();
					if (block_type != "ret") {
						if (current_func_type == "int") {
							std::cout << "\tret 0" << std::endl;
						} else if (current_func_type == "void") {
							std::cout << "\tret" << std::endl;
						} else {
							assert(false);
						}
					}
					
					// generate the final part --> }\n\n and the return the block_type
					std::cout << "}" << std::endl << std::endl;
					return block_type;
				}
				
};

class FuncTypeAST : public BaseAST {
		public:
				std::string ident;

				void Dump() const override {
					std::cout << "FuncTypeAST { ";
					std::cout << ident;
					std::cout << " } ";
				}

				std::string dumpIR() const override {
					// just return the type name
					return ident;
				}
};

class BlockAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> stmt;	

				void Dump() const override {
						std::cout << "BlockAST { ";
						stmt->Dump();
						std::cout << " } ";
				}

				std::string dumpIR() const override {
						// the block type is contained in the stmt's first word
						// e.g. --> block :: "{" stmt "}";
						// e.g. --> stmt  :: "return" NUMBER ":";
						std::string block_type = stmt->dumpIR();
						
						// return the block type to the FuncDefAST
						return block_type;
				}
};

class StmtAST : public BaseAST {
		public:
				std::unique_ptr<BaseAST> number;

				void Dump() const override {
						std::cout << "StmtAST { ";
						number->Dump();
						std::cout << " } ";
				}

				std::string dumpIR() const override {
						// just simply return the type like "ret"
						std::string stmt_type = "ret";
						std::string current_num = number->dumpIR();

						// generate \t ret 0 part
						std::cout << "\t" << stmt_type << "\t" << current_num << std::endl;

						return stmt_type;	
				}

				
};

class NumberAST : public BaseAST {
		public:
				std::string ident;

				void Dump() const override {
						std::cout << "NumberAST { ";
						std::cout << ident;
						std::cout << " } ";
				}

				std::string dumpIR() const override {
						return ident;
				}
};
