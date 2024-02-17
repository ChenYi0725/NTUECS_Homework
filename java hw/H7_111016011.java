import java.awt.*;
import java.awt.event.*;
import java.math.BigDecimal;

/*
 	 作者:資二甲 陳奕 111016011
	 操作說明:功能同window標準小算盤，包含加、減、乘、除、平方、正負號轉換、清除全部、清除一個
	 自評:100(包含所有功能)
	 額外功能:除法錯誤偵測、小數點計算不會有精準度問題、重複輸入的運算符號會取代原運算符號
 
 */
public class H7_111016011 extends Frame implements ActionListener{
	static H7_111016011 frm=new H7_111016011();			//建立視窗
	static boolean function=false;						//按下四則運算鍵
	static boolean calculate=false;						//是否進行運算
	static boolean error=false;							//除法是否有錯誤
	static BigDecimal zero=new BigDecimal("0");			
	static String result="0";
	static String last="0";
	static BigDecimal bd_last=new BigDecimal("0");
	static BigDecimal bd_result=new BigDecimal("0");
	static int arithmetic=0;							//記錄上個符號 0->沒有使用 1-> + |2-> - |3-> × | 4-> ÷
	static boolean decimal_point=false;					//有無使用過小數點
	static Label l_result=new Label(result,Label.RIGHT);
	static Label showlast=new Label(last,Label.RIGHT);
	
    static Panel lastinput=new Panel(new GridLayout(1,1));
    static Panel resultblock=new Panel(new GridLayout(1,1));
    static Panel bottonblock=new Panel(new GridLayout(6,4));
//-------------數字按鈕
    static Button b_0=new Button("0");
    static Button b_1=new Button("1");
    static Button b_2=new Button("2");
    static Button b_3=new Button("3");
    static Button b_4=new Button("4");
    static Button b_5=new Button("5");
    static Button b_6=new Button("6");
    static Button b_7=new Button("7");
    static Button b_8=new Button("8");
    static Button b_9=new Button("9");
//-------------功能按鈕    
    static Button b_plus		=new Button("+");
    static Button b_minus		=new Button("-");
    static Button b_multiply	=new Button("×");
    static Button b_divide		=new Button("÷");
    static Button b_equal		=new Button("=");
    static Button b_dot			=new Button(".");
    static Button b_clear		=new Button("c");
    static Button b_delete		=new Button(" ←");
	static Button b_transform	=new Button("+/-");
	static Button b_square		=new Button("x^2");	
	
	static Button b_ce			=new Button("ce");	
	static Button b_persent		=new Button("%");	
	static Button b_root		=new Button("√x");	
	static Button b_reciprocal	=new Button("1/x");	
		
	public static void main(String args[]){
	
//-------------視窗設定\
		frm.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});	//關閉視窗
		frm.setLayout(null);	//設定版面配置		
 		frm.setResizable(false);//固定視窗大小	
		frm.setSize(450,580);	//設定視窗大小
		frm.setBackground(new Color(68, 66, 122));
		frm.setTitle("小算盤");
		frm.setVisible(true);
//-------------視窗設定/		
		Font fnt=new Font("Serief",Font.ITALIC+Font.BOLD,40);		//設定字形
		lastinput.setBounds(20,40,410,25);
		resultblock.setBounds(20,65,410,55);		//X座標 Y座標 寬 高 
		bottonblock.setBounds(20,135,410,400);
		lastinput.setBackground(new Color(157, 108, 255));
		resultblock.setBackground(new Color(174, 157, 255));		
		
		l_result.setFont(fnt);
		frm.add(lastinput);
		frm.add(resultblock);
		frm.add(bottonblock);
//-------------按鈕設定\	
		b_0.addActionListener(frm);	
		b_1.addActionListener(frm);
		b_2.addActionListener(frm);
		b_3.addActionListener(frm);
		b_4.addActionListener(frm);
		b_5.addActionListener(frm);
		b_6.addActionListener(frm);
		b_7.addActionListener(frm);
		b_8.addActionListener(frm);	
		b_9.addActionListener(frm);
		b_plus.addActionListener(frm);
		b_minus.addActionListener(frm);
		b_multiply.addActionListener(frm);
		b_divide.addActionListener(frm);
		b_equal.addActionListener(frm);
		b_dot.addActionListener(frm);
		b_clear.addActionListener(frm);
		b_delete.addActionListener(frm);
		b_transform.addActionListener(frm);
		b_square.addActionListener(frm);
		
		b_ce.addActionListener(frm);
		b_persent.addActionListener(frm);	
		b_root.addActionListener(frm);	
		b_reciprocal.addActionListener(frm);
		

//-------------按鈕設定/	
		
//-------------新增按鈕\	
		bottonblock.add(b_persent);
		bottonblock.add(b_root);
		bottonblock.add(b_square);
		bottonblock.add(b_reciprocal);
			
		bottonblock.add(b_ce);
		bottonblock.add(b_clear);
		bottonblock.add(b_delete);
		bottonblock.add(b_divide);
		
		bottonblock.add(b_7);
		bottonblock.add(b_8);
		bottonblock.add(b_9);
		bottonblock.add(b_multiply);
		
		bottonblock.add(b_4);
		bottonblock.add(b_5);
		bottonblock.add(b_6);
		bottonblock.add(b_minus);
		
		bottonblock.add(b_1);
		bottonblock.add(b_2);
		bottonblock.add(b_3);
		bottonblock.add(b_plus);
		
		bottonblock.add(b_transform);
		bottonblock.add(b_0);
		bottonblock.add(b_dot);
		bottonblock.add(b_equal);
//-------------新增按鈕/				
		resultblock.add(l_result);
		lastinput.add(showlast);

	}


//---------按鈕動作\	
	public void actionPerformed(ActionEvent e){
		Button click=(Button) e.getSource();
		
		if(click==b_dot&&!decimal_point){							//按下小數點
			decimal_point=true;
			result=result+".";
		}

		if(click==b_clear){											//按下清除->全部設為預設值
			result="0";
			decimal_point=false;
			last="0";
			showlast.setText(last);	
			error=false;	
		}
		
		if(click==b_delete){										//後退鍵			
			if(result.charAt(result.length()-1)=='.'){				//如果刪除小數點
				decimal_point=false;
			}	
			if(result.length()>0){									
				result=result.substring(0,result.length()-1);
				if(result.length()==0){								//如果刪到最後一位
					result="0";
				}
			}
		}
		
		
//------------------按下數字鍵\		
		if(click==b_1){								//按下數字鍵->把數字放在最後一位
			result=result+"1";
			function=false;
		}else if(click==b_2){
			result=result+"2";
			function=false;
		}else if(click==b_3){
			result=result+"3";
			function=false;
		}else if(click==b_4){
			result=result+"4";
			function=false;
		}else if(click==b_5){
			result=result+"5";
			function=false;
		}else if(click==b_6){
			result=result+"6";
			function=false;
		}else if(click==b_7){
			result=result+"7";
			function=false;
		}else if(click==b_8){
			result=result+"8";
			function=false;
		}else if(click==b_9){
			result=result+"9";
			function=false;
		}else if(click==b_0){
			if(!(result.charAt(result.length()-1)=='0'&&decimal_point)){			
				result=result+"0";
			}	
			function=false;
		}
		
		
		if(result.charAt(0)=='0'&&result.length()>1&&click!=b_dot){		//在0的時候按下其他數字可替代0
			result=result.substring(1,result.length());
		}
//------------------按下數字鍵/	

		bd_result=new BigDecimal(result);
		
//------------------運算鍵\		
		if(click==b_ce){					//清除當前輸入
			bd_result=new BigDecimal("0");
		}
		
		if(click==b_persent){				//百分比
			bd_result=bd_result.divide(new BigDecimal("100"));
		}
					
		if(click==b_root){					//根號
			double a=bd_result.doubleValue();
			a=Math.pow(a,0.5);
			bd_result=new BigDecimal(a).setScale(8,BigDecimal.ROUND_HALF_UP);
			
			
		}
		
		if(click==b_reciprocal){			//倒數
					
			try{
				bd_result=new BigDecimal("1").divide(bd_result,8,BigDecimal.ROUND_HALF_UP);
			}catch(Exception ex){
				error=true;
			}
		}
		if(click==b_square){										//平方
			bd_result=bd_result.multiply(bd_result);
			function=true;
			arithmetic=0;
		}
		
		if(click==b_transform){										//正負號轉換
			bd_result=zero.subtract(bd_result);
		}


		if(last.charAt(last.length()-1)=='+'||last.charAt(last.length()-1)=='-'||last.charAt(last.length()-1)=='×'||last.charAt(last.length()-1)=='÷'){		//如果last最後一個字元是運算符號->計算並丟回
//-----------------如果運算元重複輸入\
				if(click==b_equal&&function){	
					last=last.substring(0,last.length()-1);
					arithmetic=0;
				}else if(click==b_plus&&function){
					last=last.substring(0,last.length()-1);
					last=last+"+";	
					arithmetic=1;
				}else if(click==b_minus&&function){
					last=last.substring(0,last.length()-1);
					last=last+"-";	
					arithmetic=2;
				}else if(click==b_multiply&&function){
					last=last.substring(0,last.length()-1);
					last=last+"×";
					arithmetic=3;
				}else if(click==b_divide&&function){
					last=last.substring(0,last.length()-1);
					last=last+"÷";
					arithmetic=4;
				}
//------------------如果運算元重複輸入/
//------------------運算\	
			if(click==b_equal&&!function){	
				bd_last=new BigDecimal(last.substring(0,last.length()-1));		//把last的數字部分取出
				switch(arithmetic){
					case 1:
						bd_result=bd_result.add(bd_last);
						break;
					case 2:
						bd_result=bd_last.subtract(bd_result);
						break;
					case 3:
						bd_result=bd_result.multiply(bd_last);
						break;
					case 4:
						try{
							bd_result=bd_last.divide(bd_result,8,BigDecimal.ROUND_HALF_UP);
						}catch(Exception ex){
							error=true;
						}
						
						break;	
				}
				last="0";
				function=true;
				calculate=true;
			}else if(click==b_plus&&!function){
				bd_last=new BigDecimal(last.substring(0,last.length()-1));		//把last的數字部分取出
				switch(arithmetic){												//根據arithmetic決定進行何種運算
					case 1:
						bd_result=bd_result.add(bd_last);
						break;
					case 2:
						bd_result=bd_last.subtract(bd_result);
						break;
					case 3:
						bd_result=bd_result.multiply(bd_last);
						break;
					case 4:
						try{
							bd_result=bd_last.divide(bd_result,8,BigDecimal.ROUND_HALF_UP);
						}catch(Exception ex){
							error=true;
						}
						break;	
				}
				last=bd_result.toPlainString();													
				last=last+"+";														//把last放回螢幕
				arithmetic=1;
				function=true;
				calculate=true;
			}else if(click==b_minus&&!function){
				bd_last=new BigDecimal(last.substring(0,last.length()-1));		//把last的數字部分取出
				switch(arithmetic){												//根據arithmetic決定進行何種運算
					case 1:
						bd_result=bd_result.add(bd_last);
						break;
					case 2:
						bd_result=bd_last.subtract(bd_result);
						break;
					case 3:
						bd_result=bd_result.multiply(bd_last);
						break;
					case 4:
						try{
							bd_result=bd_last.divide(bd_result,8,BigDecimal.ROUND_HALF_UP);
						}catch(Exception ex){
							error=true;
						}
						break;	
				}
				last=bd_result.toPlainString();													
				last=last+"-";													//把last放回螢幕
				arithmetic=2;
				function=true;	
				calculate=true;
			}else if(click==b_multiply&&!function){
				bd_last=new BigDecimal(last.substring(0,last.length()-1));		//把last的數字部分取出
				switch(arithmetic){												//根據arithmetic決定進行何種運算
					case 1:
						bd_result=bd_result.add(bd_last);
						break;
					case 2:
						bd_result=bd_last.subtract(bd_result);
						break;
					case 3:
						bd_result=bd_result.multiply(bd_last);
						break;
					case 4:
						try{
							bd_result=bd_last.divide(bd_result,8,BigDecimal.ROUND_HALF_UP);
						}catch(Exception ex){
							error=true;
						}
						break;	
				}
				last=bd_result.toPlainString();													
				last=last+"×";													//把last放回螢幕
				arithmetic=3;
				function=true;	
				calculate=true;
			}else if(click==b_divide&&!function){
				bd_last=new BigDecimal(last.substring(0,last.length()-1));		//把last的數字部分取出
				switch(arithmetic){												//根據arithmetic決定進行何種運算
					case 1:
						bd_result=bd_result.add(bd_last);
						break;
					case 2:
						bd_result=bd_last.subtract(bd_result);
						break;
					case 3:
						bd_result=bd_result.multiply(bd_last);
						break;
					case 4:
						try{
							bd_result=bd_last.divide(bd_result,8,BigDecimal.ROUND_HALF_UP);
						}catch(Exception ex){
							error=true;
						}
						
						
						break;	
				}
				last=bd_result.toPlainString();													
				last=last+"÷";								//把last放回螢幕
				arithmetic=4;
				function=true;
				calculate=true;
			}
							
//------------------運算/	
	
	
		}else{																	//如果last最後一個字元不是運算符號->往上丟
			if(click==b_equal){
				last=result;
				arithmetic=0;
				bd_result=new BigDecimal("0");		
				function=true;	
			}
			if(click==b_plus){
				last=result+"+";
				arithmetic=1;
				bd_result=new BigDecimal("0");	
				function=true;	
			}
			if(click==b_minus){
				last=result+"-";
				arithmetic=2;
				bd_result=new BigDecimal("0");	
				function=true;	
			}
			if(click==b_multiply){
				last=result+"×";
				arithmetic=3;
				bd_result=new BigDecimal("0");	
				function=true;	
			}
			if(click==b_divide){
				last=result+"÷";
				arithmetic=4;
				bd_result=new BigDecimal("0");	
				function=true;		
			}	
		}
	
		if(function){						//如果上個輸入是符號
			decimal_point=false;
			showlast.setText(last);	
		}

//------------------運算鍵/	
	
	
		
		
		if(click==b_dot){														//如果該次輸入小數點
			result=bd_result.toPlainString()+".";
		}else{
			result=bd_result.toPlainString();
		}	
		
		if(error){																//如果在除法時發生錯誤 x除數=0
			l_result.setText("錯誤");
			error=false;
		}else{
			l_result.setText(result);
		}
		
		if(calculate){															//如果剛剛進行過運算->把result歸零
			result="0";
			calculate=false;
		}


	}
	
	
}
