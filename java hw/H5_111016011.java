//import java.util.Scanner;
import java.util.*;
/*
  作者:資二甲 陳奕 111016011
  操作說明:輸入一中序式，系統會輸出其前序式
  自評:100 功能皆有達成，可支援括號
  額外功能:可重複使用、可辨別輸入是否錯誤
 */

public class H5_111016011{
	
    public static int priority(char a){		//定義運算子優先順序
        switch (a){
            case '+':
            	return 1;
            case '-':
                return 1;
            case '*':
            	return 2;
            case '/':
                return 2;
            default:
                return 0;
        }
    }	
    
    public static boolean legal(String a){			//檢查輸入中序式是否正確
    	int brackets=0;
    	boolean check=true;
    	char p;
    	char l=a.charAt(a.length()-1); 
	    if(l!='1'&&l!='2'&&l!='3'&&l!='4'&&l!='5'&&l!='6'&&l!='7'&&l!='8'&&l!='9'&&l!='0'&&l!=')'){	//檢查最後一位
			check=false;
	    }
	    l=a.charAt(0);
	    if(l!='1'&&l!='2'&&l!='3'&&l!='4'&&l!='5'&&l!='6'&&l!='7'&&l!='8'&&l!='9'&&l!='0'&&l!=')'){	//檢查第一位
			check=false;
	    }
    	for (int i=0;i<a.length()-1;i++) {	//一個一個檢查        	
    		if(a.charAt(i)=='+'||a.charAt(i)=='-'||a.charAt(i)=='*'||a.charAt(i)=='/'){	//檢查有無連續四則運算子
    			if(a.charAt(i+1)=='+'||a.charAt(i+1)=='-'||a.charAt(i+1)=='*'||a.charAt(i+1)=='/'||a.charAt(i+1)==')'){
    				check=false;
    			}
    		}
	    	
	    }
	    for (int i=0;i<a.length();i++) {	//一個一個檢查        	
 //---------------------------檢查括號     	
    		if(a.charAt(i)=='(') {			//左括號+1
	        	brackets=brackets+1;
	        }
	        if(a.charAt(i)==')') {			//右括號-1
	        	brackets=brackets-1;
	        }
	        if(brackets<0){						//如果有右括號比左括號早出現->brackets無法等於0
	            brackets= -2;
	        }
//---------------------------檢查括號 
	    }

	    
	   	if(brackets!=0){		//如果括號有錯
	    	check=false;
	    }
	    
    	return check;
    	
    }
	
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		String re;									//重複使用	
		String st;									//抓出堆疊頂部
		char p;									//當前檢查到的字元
		String input="";
		int brackets;						//檢查括號是否成對
		Stack<String> output= new Stack();			//輸出的stack
		Stack<String> reversedoutput= new Stack();
		Stack<Character> operator= new Stack();		//儲存運算子的stack
		
		while(true){								//重複使用的大迴圈
			while(true){				//檢查輸入是否正確
				brackets=0;
				System.out.println("請輸入一中序式");
				input=scan.nextLine();					
				
				if(legal(input)){		//如果輸入正確(使用前方函式)
					String infix[]=new String[input.length()];		//建立一陣列儲存運算元與運算子
					infix=input.split("((?<=\\D)|(?=\\D))");		//用數字分割並保留
								
					for(int i=infix.length-1;i>=0;i--){				//從尾巴開始讀
					//	System.out.println(infix[i]+" ");
						p=infix[i].charAt(0);						//當前讀到字串的第一個字元(因只需特別判斷運算子，所以只取一個)
						
						if(p=='+'||p=='-'||p=='*'||p=='/'){				//若當前為運算子且非括號
							
							if(operator.empty()){									//如果stack是空的
								operator.push(p);
							}
							else if(priority(p)>=priority(operator.peek())){	//優先序>=堆疊頂部則push
								operator.push(p);
							}else{													//若優先序<堆疊頂部
								while(!operator.empty()){
									output.push(Character.toString(operator.pop()));	//丟到輸出堆疊
									
									if(operator.empty()){									//如果stack是空的
										operator.push(p);
										break;
									}else if(priority(p)>=priority(operator.peek())){	//優先序>=堆疊頂部
										operator.push(p);
										break;
									}
									
								}
	
							}
																	
							
						}else if(p==')'){										//若當前運算子為右括號
							operator.push(p);
						
						
						}else if(p=='('){										//若當前運算子為左括號
							while(!operator.empty()){
								output.push(Character.toString(operator.pop()));					
								if(operator.peek()==')'){
									operator.pop();
									break;
								}
							}
							
						}else{													//若當前為運算元
							output.push(infix[i]);				
						}
					}
					break;
				}else{					//如果輸入錯誤
					System.out.println("中序式輸入錯誤，請重新輸入");
				}			
			}
			
			while(!operator.empty()){						//把operator全丟進去output
				output.push(Character.toString(operator.pop()));
			}
			
			System.out.print("前序式:");
			while(!output.empty()){					//輸出
				System.out.print(output.pop()+" ");
			}
			
			
					
//------------------重新使用	
				
			System.out.println("\n是否再使用一次(輸入1繼續，輸入0退出)");	//重新輸入迴圈
			re=scan.nextLine();
			
			while(!(re.contains("1")||re.contains("0"))||re.length()!=1){						//檢查是否為1或0
				System.out.println("請重新輸入(輸入1繼續，輸入0退出)");
				re=scan.nextLine();
				if((re.contains("1")||re.contains("0"))&&re.length()==1){
					break;
				}				
			}
			
			if(re.contains("0")){			//0直接結束
				break;
			}
		}
	System.out.println("謝謝您的使用");
		
	}
}
