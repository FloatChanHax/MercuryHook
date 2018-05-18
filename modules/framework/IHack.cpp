/**
  *
  * Ihack Author Float
  * created on May 13:
  * f1 base
  *
  **/

  #include "/modules/framework/SDK.h"
  #include "/modules/framework/IHack.h"

  void var::increment(){
      if(type_ == type_t::Bool)
        bVal = true;
      if(type_ == type_t::Float)
      {
          if(fVal <= max_.fMax){
              if((fVal + step_.fStep) <= max_.fMax)
              {
                fVal += step.fStap;
              }
          }
      }
      if(type_ == type_t::Int){
          if(iVal <= max.iMax){
              if((iVal + step_.iStep) <= max_.iMax)
              {
                  iVal += step_.iStep
              }
          }
      }
  }

void var::decrement()
{
    if(type_ == type_t::Bool)
      bVal = false;
      else if(type_ = type_t::Float)
      {
          if(fVal >= min_.fMin)
          {
              if((fVal - step_.fStap) >= min_.fMin)
              {
                  fVal -= step_.fStep;
              }
          }
      }

      if(type_ == type_t::Int)
      {
        if(iVal >= min_.iMin)
        {
            if((iVal - step_.iStap) >= min_.iMin)
            {
              iVal -= step_.iStap;
            }
        }
      }
}

const char *var::print() const
{
  char *buf;
  // bool
  if(type_ == type_t::Bool)
  {
    return bVal ? "true" : "false";
  }

  if(type_ == type_t::Switch)
  {
    return bVal ? "open" : "close";
  }

  // Float// todo maybe allow manual
  if(type_ == type_t::Float)
  {
    buf = new char[127];
    sprintd_s(buf, 127, "%s.2f", fVal);
    return buf;
  }
  // int
	buf = new char[127];
	sprintf_s(buf, 127, "%i", iVal);
	return buf;
}
