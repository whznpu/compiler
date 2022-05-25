#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "AST.h"
#include <fstream>
// #include "koopa_parse.h"
#include <unistd.h>
#include <getopt.h>
#include<errno.h>
#include <string.h>
#include<sstream>

using namespace std;

    
// struct option {
//   const char * name;  // 参数的名称
//   int has_arg; // 是否带参数值，有三种：no_argument， required_argument，optional_argument
//   int * flag; // 为空时，函数直接将 val 的数值从getopt_long的返回值返回出去，
//           // 当非空时，val的值会被赋到 flag 指向的整型数中，而函数返回值为0
//   int val; // 用于指定函数找到该选项时的返回值，或者当flag非空时指定flag指向的数据的值
// };
        /*
    其中：
        no_argument(即0)，表明这个长参数不带参数（即不带数值，如：--name）
            required_argument(即1)，表明这个长参数必须带参数（即必须带数值，如：--name Bob）
            optional_argument(即2)，表明这个长参数后面带的参数是可选的，（即--name和--name Bob均可）
     */



// 声明 lexer 的输入, 以及 parser 函数
// 为什么不引用 sysy.tab.hpp 呢? 因为首先里面没有 yyin 的定义
// 其次, 因为这个文件不是我们自己写的, 而是被 Bison 生成出来的
// 你的代码编辑器/IDE 很可能找不到这个文件, 然后会给你报错 (虽然编译不会出错)
// 看起来会很烦人, 于是干脆采用这种看起来 dirty 但实际很有效的手段
extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &ast);
extern char *optarg;


string s="";
stringstream BaseAST::ss(s);

int main(int argc, char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler  输入文件 -o 输出文件
  assert(argc == 4);\
  const char* input;
  const char* output;
  input=argv[1];

  int ch;
  while((ch=getopt(argc,argv,"o:"))!=-1){
    switch(ch){
      case 'o':
          output=optarg;
        break;
    }

  }
  
  // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
  yyin = fopen(input, "r");
  assert(yyin);

  // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
  unique_ptr<BaseAST> ast;
  
  auto ret = yyparse(ast);
  assert(!ret);
  // 输出解析得到的 AST, 其实就是个字符串
  ast->Dump();
  cout<<BaseAST::ss.str();
  freopen(output,"w",stdout);

  return 0;
}
