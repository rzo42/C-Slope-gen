# C++-Slope-gen
C++ slope generator

SLOPE CLASS DEMO
BY: RYAN LISTON
LANGUAGE: C++
TARGET: ARDUNO (NOT LIMITED TO)
DATE: 02/15/2022 
DESCRIPTION: A DEMONSTRATION OF SLOPE CLASS GENERATING ADSR STYLE ENVELOPE. SLOPE CLASS GENERATES LINEAR, LOGORITMIC AND LINEAR STYLE SLOPES.

------------------------------------------------------------------------------------------------------ 

KEY WORDS

  SLOPE : class name
        Use to initialize a slope as an object.
          examples :  SLOPE attack;
                      SLOPE _Release;
                      SLOPE DECAY;
              *once a slope object has been initialized and its attributes set it can be used to generate multiple style slopes with the 
                same attributes.

  .Base() : Function to set base value. 
        The base defines the curve of the slope for the exponential and logorithmic slopes. 
         Values between e(2.71828...) and 10. Base is set to a default value of 10.
            examples :  attack.Base(e);
                        release.Base(7);  

  .Duration() : Function for setting the duration of a slope.
         Duration is the length of a curve or the time it takes it to execute.
         Duration is set to a defaulr value of 2500
            examples :  release.Duration(5);
                        decay.Duration(5000);
  
  .Gain() : Function for setting the peak level of the slope.
         Gain is set to a defaulr value of 255
            example :   attack.Gain(255);
                        attack.Gain(Max_Vol);

  .Offset() : Function for setting the base offset.
         The base offset sets y1 to 0 and y2 to <Duration> relative to the base value.
         Formula for producung offset: log(base)/base 
         Offset is set to a defaulr value of 0.1
            examples:   attack.Offset(log(10)/10);
                        release.Offset(.1);

  .Threshold : Function for setting the Threshold (floor) of a slope.
          The threshhold is the floor or bottom of a slope.
          Threshold is set to a defaulr value of 0 
              example:  decay.Threshold(100);
                        decay.Threshold(0);

  .Exp : Function for generating an exponential slope.
          example :  decay.Exp(_time)

  .Log : Function for generating a logorithmic slope.
          example :  decay.Log(_time)

  .Lin : Function for generating a linear slope.
          example :  decay.Lin(_time)

  .RevExp : Function for generating a reversed exponential slope.
          example :  decay.RevExp(_time)

  .RevLog : Function for generating a reversed logorithmic slope.
          example :  decay.RevLog(_time)

  .RevLin : Function for generating a reversed linear slope.
          example :  decay.Exp(_time)

-----------------------------------------------------------------
