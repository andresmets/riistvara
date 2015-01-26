#include <8051.h>

unsigned int commaSection = -1;
//numbrid 0-9 + C,F,-,E
const signed char displayvalues[]={192,249,164,176,153,146,130,248,128,144,198,142,191,134};
//0-paremalt 1. 1- paremalt 2., 2- paremalt 3, 3- paremalt 4. 
const signed char displaysection[] = {14,13,11,7};
//0-50 positiivsed; 51-100 negatiivsed
const signed char c_to_f[101][5] = {
{3,2,11,-1,-1},{3,3,8,11,2},{3,5,6,11,2},{3,7,4,11,2},{3,9,2,11,2}
,{4,1,11,-1,-1},{4,2,8,11,2},{4,4,6,11,2},{4,6,4,11,2},{4,8,2,11,2}
,{5,0,11,-1,-1},{5,1,8,11,2},{5,3,6,11,2},{5,5,4,11,2},{5,7,2,11,2}
,{5,9,11,-1,-1},{6,0,8,11,2},{6,2,6,11,2},{6,4,4,11,2},{6,6,2,11,2}
,{6,8,11,-1,-1},{6,9,8,11,2},{7,1,6,11,2},{7,3,4,11,2},{7,5,2,11,2}
,{7,7,11,-1,-1},{7,8,8,11,2},{8,0,6,11,2},{8,2,4,11,2},{8,4,2,11,2}
,{8,6,11,-1,-1},{8,7,8,11,2},{8,9,6,11,2},{9,1,4,11,2},{9,3,2,11,2}
,{9,5,11,-1,-1},{9,6,8,11,2},{9,8,6,11,2},{1,0,0,11,-1},{1,0,2,11,-1}
,{1,0,4,11,-1},{1,0,6,11,-1},{1,0,8,11,-1},{1,0,9,11,-1},{1,1,1,11,-11}
,{1,1,3,11,-1},{1,1,5,11,-1},{1,1,7,11,-1},{1,1,8,11,-1},{1,2,0,11,-1}
,{1,2,2,11,-1}
,{3,0,2,11,2},{2,8,4,11,2},{2,6,6,11,2},{2,4,8,11,2}
,{2,3,11,-1,-1},{2,1,2,11,2},{1,9,4,11,2},{1,7,6,11,2},{1,5,8,11,2}
,{1,4,11,-1,-1},{1,2,2,11,2},{1,0,4,11,2},{8,6,11,-1,3},{6,8,11,-1,3}
,{5,11,-1,-1,-1},{3,2,11,-1,3},{1,4,11,-1,3},{12,0,4,11,2},{12,2,2,11,2}
,{12,4,11,-1,-1},{12,5,8,11,2},{12,7,6,11,2},{12,9,4,11,2},{12,1,1,11,-1}
,{12,1,3,11,-1},{12,1,5,11,-1},{12,1,7,11,-1},{12,1,8,11,-1},{12,2,0,11,-1}
,{12,2,2,11,-1},{12,2,4,11,-1},{12,2,6,11,-1},{12,2,7,11,-1},{12,2,9,11,-1}
,{12,3,1,11,-1},{12,3,3,11,-1},{12,3,5,11,-1},{12,3,6,11,-1},{12,3,8,11,-1}
,{12,4,0,11,-1},{12,4,2,11,-1},{12,4,4,11,-1},{12,4,5,11,-1},{12,4,7,11,-1}
,{12,4,9,11,-1},{12,5,1,11,-1},{12,5,2,11,-1},{12,5,4,11,-1},{12,5,6,11,-1}
,{12,5,8,11,-1}
};
const signed char f_to_c[181][5] = {
{12,1,7,8,1},{12,1,7,2,1},{12,1,6,7,1},{12,1,6,1,1},{12,1,5,6,1}
,{12,1,5,-1,-1},{12,1,4,4,1},{12,1,3,9,1},{12,1,3,3,1},{12,1,2,8,1}
,{12,1,2,2,1},{12,1,1,7,1},{12,1,1,1,1},{12,1,0,6,1},{12,1,0,-1,-1}
,{12,9,4,4,2},{12,8,8,9,2},{12,8,3,3,2},{12,7,7,8,2},{12,7,2,2,2}
,{12,6,6,7,2},{12,6,1,1,2},{12,5,5,6,2},{12,5,-1,-1,-1},{12,4,4,4,2}
,{12,3,8,9,2},{12,3,3,3,2},{12,2,7,8,2},{12,2,2,2,2},{12,1,6,7,2}
,{12,1,1,1,2},{12,0,5,6,2},{0,-1,-1,-1,-1},{0,5,5,6,3},{1,1,1,1,3}
,{1,6,6,7,3},{2,2,2,2,3},{2,7,7,8,3},{3,3,3,3,3},{3,8,8,9,3}
,{4,4,4,4,3},{5,-1,-1,-1,-1},{5,5,5,6,3},{6,1,1,1,3},{6,6,6,7,3}
,{7,2,2,2,3},{7,7,7,8,3},{8,3,3,3,3},{8,8,8,9,3},{9,4,4,4,3}
,{1,0,-1,-1,-1},{1,0,5,6,2},{1,1,1,1,2},{1,1,6,7,2},{1,2,2,2,2}
,{1,2,7,8,2},{1,3,3,3,2},{1,3,8,9,2},{1,4,4,4,2},{1,5,-1,-1,-1}
,{1,5,5,6,2},{1,6,1,1,2},{1,6,6,7,2},{1,7,2,2,2},{1,7,7,8,2}
,{1,8,3,3,2},{1,8,8,9,2},{1,9,4,4,2},{2,0,-1,-1,-1},{2,0,5,6,2}
,{2,1,1,1,2},{2,1,6,7,2},{2,2,2,2,2},{2,2,7,8,2},{2,3,3,3,2}
,{2,3,8,9,2},{2,4,4,4,2},{2,5,-1,-1,-1},{2,5,5,6,2},{2,6,1,1,2}
,{2,6,6,7,2},{2,7,2,2,2},{2,7,7,8,2},{2,8,3,3,2},{2,8,8,9,2}
,{2,9,4,4,2},{3,0,-1,-1,-1},{3,0,5,6,2},{3,1,1,1,2},{3,1,6,7,2}
,{3,2,2,2,2},{3,2,7,8,2},{3,3,3,3,2},{3,3,8,9,2},{3,4,4,4,2}
,{3,5,-1,-1,-1},{3,5,5,6,2},{3,6,1,1,2},{3,6,6,7,2},{3,7,2,2,2}
,{3,7,7,8,2},{3,8,3,3,2},{3,8,8,9,2},{3,9,4,4,2},{4,0,-1,-1,-1}
,{4,0,5,6,2},{4,1,1,1,2},{4,1,6,7,2},{4,2,2,2,2},{4,2,7,8,2}
,{4,3,3,3,2},{4,3,8,9,2},{4,4,4,4,2},{4,5,-1,-1,-1},{4,5,5,5,2}
,{4,6,1,1,2},{4,6,6,7,2},{4,7,2,2,2},{4,7,7,8,2},{4,8,3,3,2}
,{4,8,8,9,2},{4,9,4,4,2},{5,0,-1,-1,-1}
,{12,1,8,3,1},{12,1,8,8,1}
,{12,1,9,4,1},{12,2,0,-1,-1},{12,2,0,6,1},{12,2,1,1,1},{12,2,1,7,1}
,{12,2,2,2,1},{12,2,2,8,1},{12,2,3,3,1},{12,2,3,9,1},{12,2,4,4,1}
,{12,2,5,-1,-1},{12,2,5,6,1},{12,2,6,1,1},{12,2,6,7,1},{12,2,7,2,1}
,{12,2,7,8,1},{12,2,8,3,1},{12,2,8,9,1},{12,2,9,4,1},{12,3,0,-1,-1}
,{12,3,0,6,1},{12,3,1,1,1},{12,3,1,7,1},{12,3,2,2,1},{12,3,2,8,1}
,{12,3,3,3,1},{12,3,3,9,1},{12,3,4,4,1},{12,3,5,-1,-1},{12,3,5,6,1}
,{12,3,6,1,1},{12,3,6,7,1},{12,3,7,2,1},{12,3,7,8,1},{12,3,8,3,1}
,{12,3,8,9,1},{12,3,9,4,1},{12,4,0,-1,-1},{12,4,0,6,1},{12,4,1,1,1}
,{12,4,1,7,1},{12,4,2,2,1},{12,4,2,8,1},{12,4,3,3,1},{12,4,3,9,1}
,{12,4,4,4,1},{12,4,5,-1,-1},{12,4,5,6,1},{12,4,6,1,1},{12,4,6,7,1}
,{12,4,7,2,1},{12,4,7,8,1},{12,4,8,3,1},{12,4,8,9,1},{12,4,9,4,1}
,{12,5,0,-1,-1}
};
void clearNumArray(unsigned int numbers[]){
	numbers[0] = -1;
	numbers[1] = -1;
	numbers[2] = -1;
	numbers[3] = -1;
}

unsigned char getNumLength(unsigned int number[]){
	char i;
	for(i=sizeof(number);i>=0;i--){
		if(number[i] != -1){
			if(number[0] == 12){
				return i;
			}else{
				return i+1;
			}
		}
	}
	return 0;
}
unsigned char getMultiplier(signed int lenght){
	if(lenght == 3){
		return 100;	
	}
	if(lenght == 2){
		return 10;
	}
	return 1;
}

unsigned int getDecimalnumber(unsigned int number[]){
	int j=0,i=0,k = 0;
	unsigned char lenght = getNumLength(number);
	int sign = 1;
	unsigned char multiplier = getMultiplier(lenght);
	if(number[0] == 12){
		sign = -1;
		i=1;
	}
	for(;j<lenght;j++){
		k = k + (multiplier * number[j+i]);
		multiplier = multiplier/10;
	}
	return k * sign;	
}
void setNumberForView(unsigned int number[], int index, int fahrenheit){
	if(fahrenheit){
		number[0] = f_to_c[index][0];
		number[1] = f_to_c[index][1];
		number[2] = f_to_c[index][2];
		number[3] = f_to_c[index][3];
		commaSection = f_to_c[index][4]; 
		return;
	}
	number[0] = c_to_f[index][0];
	number[1] = c_to_f[index][1];
	number[2] = c_to_f[index][2];
	number[3] = c_to_f[index][3];
	commaSection = c_to_f[index][4];		
}
void setToError(unsigned int number[]){
	clearNumArray(number);
	number[0] = 13; //Error
	commaSection = -1;
}
int getArrayIndex(int decimal, int negBase){
	if(decimal < 0){
		return (decimal * -1) + negBase;
	}
	return decimal;
}
void convToCelsius(unsigned int number[]){
	int decimal = getDecimalnumber(number);
	if(decimal > 122 || decimal < -58){
		setToError(number);
		return;
	}	
	setNumberForView(number, getArrayIndex(decimal, 122), 1);
}

void convToFahrenheit(unsigned int number[]){
	int decimal = getDecimalnumber(number);
	if(decimal > 50 || decimal < -50){
		setToError(number);
		return;
	}
	setNumberForView(number, getArrayIndex(decimal, 50), 0);
}

void writePreviousNum(unsigned int enteredumbers[]){
	int i;
	int highestBit=0;
	P2 = 0xFF;
	P3 = 0xFF;
	for(i=sizeof(enteredumbers);i>=0;i--){
		if(enteredumbers[i] != -1){
			if(i > highestBit){
				highestBit = i;
			}
			P2 = 0xFF;			
			P3 = displaysection[highestBit - i];
			P2 = displayvalues[enteredumbers[i]];
			if((highestBit - i) == commaSection){
				P2_7=0;		
			}
		}
	}	
}
unsigned int display_value(unsigned int value, unsigned int number[]) __reentrant
{
    unsigned int retVal = 0;
    switch (value)
    {
        case 1:
            retVal = 1;
            break;
        case 2:
            retVal = 2;
            break;
        case 4:
            retVal = 3;
            break;
        case 8:
            P2 = 0xFF;
	    P3 = 0xFF;
            convToFahrenheit(number);
            retVal = -2; // A
            break;
        case 16:
            retVal = 4; // 4
            break;
        case 32:
            retVal = 5; // 5
            break;
        case 64:
            retVal = 6; // 6
            break;
        case 128:
            retVal = -1; // B
            break;
        case 256:
            retVal = 7; // 7
            break;
        case 512:
            retVal = 8; // 8
            break;
        case 1024:
            retVal = 9; // 9
            break;
        case 2048:
            P2 = 0xFF;
	    P3 = 0xFF;
            convToCelsius(number);
            retVal = -2; // C
            break;
        case 4096: // * koma ei saa sisestada
            retVal = -1;
            break;
        case 8192:
            retVal = 0; // 0
            break;
        case 16384: // # clear
            clearNumArray(number);
            retVal=-2, commaSection = -1;
            break;
        case 32768:
            retVal = 12; // D miinus
            break;
        default:
	    break;	
    }
    return retVal;
}

unsigned int scan_keyboard()
{
    unsigned char pattern;
    unsigned int scan = 0; 
	
    for (pattern = 0x10; pattern > 0; pattern <<= 1)
    {
        P1 = ~pattern; //  construct and apply pattern to read next column 
        scan = (scan << 4) | (~P1 & 0x0F);  // save result to scan variable
    }
    return scan;
}


void main()
{
    unsigned int result = 0;
    unsigned int count = 0;
    unsigned int enteredNum[4] = {-1,-1,-1,-1};
    unsigned int prevVal=-1;
    unsigned int startedEnter=-1;
    while (1)
    {
    	writePreviousNum(enteredNum);
        result = scan_keyboard();
        if(result > 0){
        	prevVal = result;
		startedEnter = 1;
        }// nupu lahtilaskmisel loetakse arv sisestatuks
        if(result == 0 && startedEnter == 1){
        	//kontroll kui vajutati clear- tagastab -1(clear nupu registreerimisel 			//massiiv nullida), ei ole vaja arvu massiivi lisada
        	//vale char samuti tagastab -1 ei ole vaja massiivi lisada
        	//kui on ületäitumine, siis tühjendada massiiv
        	if(count == 0 && enteredNum[3] != -1){
			clearNumArray(enteredNum);	
        	}	
 	        prevVal = display_value(prevVal, enteredNum);
 	        if(prevVal == -2){
			count = 0;
 	        }
 	        if(prevVal != -1 && prevVal != -2){
 	        	if(prevVal == 12){
				enteredNum[0] = prevVal;
 	        	}else{	
		        	enteredNum[count] = prevVal;
		        }
		        count ++;
		        if(count > 3){
				count = 0;
		        }
	        }
	        startedEnter = -1;
        }
    }
}