//SLOPE CLASS DEMO
//BY: RYAN LISTON
//LANGUAGE: C++
//TARGET: ARDUNO (NOT LIMITED TO)
//DATE: 02/15/2022 
//DESCRIPTION: A DEMONSTRATION OF SLOPE CLASS GENERATING ADSR STYLE ENVELOPE. SLOPE CLASS GENERATES LINEAR, LOGORITMIC AND LINEAR STYLE SLOPES.
//----------------------------------------------------------------------------------------------------------------------------------------------
//KEY WORDS
//
//  SLOPE : class name
//        Use to initialize a slope as an object.
//          examples :  SLOPE attack;
//                      SLOPE _Release;
//                      SLOPE DECAY;
//              *once a slope object has been initialized and its attributes set it can be used to generate multiple style slopes with the 
//                same attributes.
//
//  .Base() : Function to set base value. 
//        The base defines the curve of the slope for the exponential and logorithmic slopes. 
//         Values between e(2.71828...) and 10. Base is set to a default value of 10.
//            examples :  attack.Base(e);
//                        release.Base(7);  
//
//  .Duration() : Function for setting the duration of a slope.
//         Duration is the length of a curve or the time it takes it to execute.
//         Duration is set to a defaulr value of 2500
//            examples :  release.Duration(5);
//                        decay.Duration(5000);
//  
//  .Gain() : Function for setting the peak level of the slope.
//         Gain is set to a defaulr value of 255
//            example :   attack.Gain(255);
//                        attack.Gain(Max_Vol);
//
//  .Offset() : Function for setting the base offset.
//         The base offset sets y1 to 0 and y2 to <Duration> relative to the base value.
//         Formula for producung offset: log(base)/base 
//         Offset is set to a defaulr value of 0.1
//            examples:   attack.Offset(log(10)/10);
//                        release.Offset(.1);
//
//  .Threshold : Function for setting the Threshold (floor) of a slope.
//          The threshhold is the floor or bottom of a slope.
//          Threshold is set to a defaulr value of 0 
//              example:  decay.Threshold(100);
//                        decay.Threshold(0);
//
//  .Exp : Function for generating an exponential slope.
//          example :  decay.Exp(_time)
//
//  .Log : Function for generating a logorithmic slope.
//          example :  decay.Log(_time)
//
//  .Lin : Function for generating a linear slope.
//          example :  decay.Lin(_time)
//
//  .RevExp : Function for generating a reversed exponential slope.
//          example :  decay.RevExp(_time)
//
//  .RevLog : Function for generating a reversed logorithmic slope.
//          example :  decay.RevLog(_time)
//
//  .RevLin : Function for generating a reversed linear slope.
//          example :  decay.Exp(_time)
//
//-----------------------------------------------------------------

//SLOPE CLASS

class SLOPE{
  
  private:    //class variables for formulas
  double _g=255;    //gain
  double _d=2500;   //duration
  double _t=0; //threshold
  double _y;   //gain offset by threshold
  double _yy;  //y offset 2
  double _Y;   //y offst 1
  double _YY;  //y offset 2 inverse for log
  double _yd;  // exponant for lin
  double Y;     //gain output
  double _b=10; //base
  double _o=.1; //base offset // (log(base)/base) produces an accurate base offset for bases from e to 10
                
  public:     // input functions // handles partial weight of the slope formulas on input 
              // in order to maxamize speed of slope execution.
  double Base(double x){_b=x;_y=_g-_t;_yy=_o*(_t-_g);_Y=(_y+_o*_y)/_b;_YY=_o*_y;_yd=_y/_d;}   // defines the curve of the slope 
  double Offset(double x){_o=x;_y=_g-_t;_yy=_o*(_t-_g);_Y=(_y+_o*_y)/_b;_YY=_o*_y;_yd=_y/_d;}  //stabalizes the slope
  double Gain(double x){_g=x;_y=_g-_t;_yy=_o*(_t-_g);_Y=(_y+_o*_y)/_b;_YY=_o*_y;_yd=_y/_d;}     //peak of the slope
  double Threshold(double x){_t=x;_y=_g-_t;_yy=_o*(_t-_g);_Y=(_y+_o*_y)/_b;_YY=_o*_y;_yd=_y/_d;} // bottom of the slope
  double Duration(double x){_d=x;_y=_g-_t;_yy=_o*(_t-_g);Y=(_y+_o*_y)/_b;_YY=_o*_y;_yd=_y/_d;}    //duration of the slope
  
            //slope functions <object_name.SlopeType(Time)>
  double Exp(double X){Y=_t+_Y*pow(_b,X/_d)-_YY;return Y;}
  double RevExp(double X){Y=_t+_Y*pow(_b,(_d-X)/_d)-_YY;return Y;}
  double Log(double X){Y=_g-_Y*pow(_b,(_d-X)/_d)-_yy;return Y;}
  double RevLog(double X){Y=_g-_Y*pow(_b,(X/_d))-_yy;return Y;}
  double Lin(double X){Y=_t+X*(_yd);return Y;}
  double RevLin(double X){Y=_g-X*(_yd);return Y;}
};

//DEMO--------------------------------------------------------------------- 

//variables for adsr envelope generation
double _gan=175;  //gain
double _att=80;   //attack duration
double _dec=60;   //decay duration
double _sus=100;  //sustain threshold level
double _rel=150;  //rlease duration
double _hold=150; //sustain duration

//output variable
double _output;   //output

//open serial channel at 9600 baud
void setup() {Serial.begin(9600);}

//-------------------------------------------------------------------------------

void loop() {

//initialize and set parameters

  SLOPE attack;     //initialize 'attack' 
  attack.Gain(_gan);  //set attack gain
  attack.Duration(_att);  // set attack duration
  
  SLOPE decay;     //initialize 'decay'
  decay.Gain(_gan);    //set decay gain 
  decay.Duration(_dec); //set decay duration
  decay.Threshold(_sus); //set sustain threshold for end point of phase

  SLOPE release_;   //initialize 'release'
  release_.Gain(_sus); //set sustain threshold for start point of phase
  release_.Duration(_rel);   //set release duration

 //------------------------------------------------------------------------------
  
 //execute attack phase
 for (double y=0;y<=_att;y++){    
  _output=attack.Lin(y);
    Serial.println(_output);
 }

 //execute decay phase
for (double y=0;y<=_dec;y++){
  _output=decay.RevLin(y);
    Serial.println(_output);
 }

 //execute sustain phase
for (double y=0;y<=_hold;y++){
  _output=_sus;
    Serial.println(_output);
 }

 //execute release phase
for (double y=0;y<=_rel;y++){
  _output=release_.RevLin(y);
    Serial.println(_output);
 }
int u=0;
while (u==0){}      
  }
