import java.util.Scanner;
/*
  作者:資二甲 陳奕 111016011
  操作說明:依序輸入年、月、日，系統會輸出當月月曆與當天的星期
  自評:100 功能皆有達成
  額外功能:在月曆上標示出輸入日期、可重複使用、可辨別輸入是否錯誤
 */
public class H4_111016011{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		String re;					//重複使用
		int year=0,month,date,days;		//目標年月日、當月有幾天
		int shift=0,week=0,dweek=0;				//1號的位移、判斷是否換行的變數、目標的星期
		boolean input;
		while(true){						//重複使用
			shift=0;						//重新設定數值
			week=0;
			dweek=0;
			input=false;		
			System.out.println("請輸入年份");
			while(true){
				try{
					year=scan.nextInt();
				}catch(Exception e){
					System.out.println("輸入錯誤，請重新輸入");
					scan.nextLine();		//忽略錯誤輸入
					continue;
				}		
				break;				
			}
			System.out.println("請輸入月份");
			while(true){
				try{
					month= scan.nextInt();
				}catch(Exception e){
					System.out.println("輸入錯誤，請重新輸入");
					scan.nextLine();		//忽略錯誤輸入
					continue;
				}		
				if(month<1||month>12){
					System.out.println("輸入錯誤，請輸入1~12月");
					continue;	
				}
				break;				
			}		
	//------------計算當月有幾天	
			if(month<=7&&month%2!=0){
				days=31;
			}else if(month>=8&&month%2==0){
				days=31;
			}else if(month==2){
				if(year%4==0){			//如果是閏年
					days=29;
				}else{
					days=28;
				}
			}else{
				days=30;
			}
	//------------計算當月有幾天
			System.out.println("請輸入日期");
			while(true){
				try{
					date= scan.nextInt();
				}catch(Exception e){
					System.out.println("輸入錯誤，請重新輸入");
					scan.nextLine();		//忽略錯誤輸入
					continue;
				}		
				if(date<1||date>days){
					System.out.println("輸入錯誤，"+month+"月只有"+days+"天");
					continue;	
				}
				break;				
			}			
	//------------計算shift
			if(year>2018){				//目標在2018後(因為2018的1/1剛好在週一)
				for(int i=2018;i<year;i++){
					if(i%4==0){
						shift=shift+2;
					}else{
						shift=shift+1;
					}
				}
			}else{
				for(int j=year;j<2018;j++){			//目標在2018年後
					if(j%4==0){
						shift=shift+2;
					}else{
						shift=shift+1;
					}
				}
				shift=7-(shift%7);
			}
			
			switch (month){							//計算每個月影響shift的程度，shift後加上的數字是當月前面所有月份的天數%7
				case 2:
					shift=shift+3;
					break;
				case 3:
					shift=shift+3;
					break;
				case 4:
					shift=shift+6;
					break;
				case 5:
					shift=shift+1;
					break;
				case 6:
					shift=shift+4;
					break;
				case 7:
					shift=shift+6;
					break;
				case 8:
					shift=shift+2;
					break;
				case 9:
					shift=shift+5;
					break;
				case 10:
					break;
				case 11:
					shift=shift+3;
					break;
				case 12:
					shift=shift+5;
					break;
				}
			if(month>2&&year%4==0){			//如果是閏年，且在2月後
				shift=shift+1;
			}
			
			shift=shift%7;			//最後確保shift<7	
			System.out.print("一\t二\t三\t四\t五\t六\t日\n");	//輸出星期
			for(int k=0;k<shift;k++){
				System.out.print("\t");
				week=week+1;
			}
			
			for(int l=1;l<days+1;l++){
				if(date==l){
					System.out.print("["+l+"]\t");		//框出目標日期
				}else if(l<10){							//輸出日期(如果只有一位數
					System.out.print(" "+l+"\t");
				}else{
					System.out.print(l+"\t");	
				}
				week=week+1;
				if(l==date){
					dweek=week;
				}
				if(week==7){
					week=0;
					System.out.print("\n");
				}
			}
			System.out.print("\n");
			System.out.print(year+"年"+month+"月"+date+"日，是星期");	
			switch(dweek){						//依照當日的星期輸出對應中文
				case 1:
					System.out.println("一");
					break;
				case 2:
					System.out.println("二");
					break;
				case 3:
					System.out.println("三");
					break;
				case 4:
					System.out.println("四");
					break;
				case 5:
					System.out.println("五");
					break;
				case 6:
					System.out.println("六");
					break;
				case 7:
					System.out.println("日");
					break;
				
			}//switch
//---------------重複使用(輸入與判斷)
			System.out.println("是否再使用一次(輸入1繼續，輸入0退出)");	//重新輸入迴圈
			re=scan.next();
			
			while(!(re.contains("1")||re.contains("0"))||re.length()!=1){						//檢查是否為1或0
				System.out.println("請重新輸入");
				re=scan.next();
				if((re.contains("1")||re.contains("0"))&&re.length()==1){
					break;
				}				
			}
			if(re.contains("0")){			//0直接結束
				break;
			}
//---------------重複使用(輸入與判斷)
		}//while	
	}
}