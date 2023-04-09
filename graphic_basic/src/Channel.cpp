#include"Channel.h"
/* if(strcmp(temp,"constant")==0){
    expIn=0;
}else if(strcmp(temp,"linear")==0){
    expIn=1;
}else if(strcmp(temp,"cycle")==0){
    expIn=2;
}else if(strcmp(temp,"cycle_offset")==0){
    expIn=3;
}else if(strcmp(temp,"bounce")==0){
    expIn=4;
}
 */
Channel::Channel(int numKeyframes,int extrapolateIn, int extrapolateOut){
    this->numKeyframes=numKeyframes;
    this->extrapolateIn=extrapolateIn;
    this->extrapolateOut=extrapolateOut;
    this->keyframes=std::vector<Keyframe*>();
}

Channel:: ~Channel(){
    
}

void Channel::addFrame(Keyframe* data){
    if(keyframes.size()==0){
        keyframes.push_back(data);
        return;
    }
    keyframes.back()->setNext(data);
    data->setLast(keyframes.back());
    keyframes.push_back(data);
}

void Channel::load(){
    //std::cout<<"occur"<<std::endl;
    for (std:: vector<Keyframe*>::iterator it = keyframes.begin(); it != keyframes.end(); it++){
        (*it)->computeTangents();
    }
    int i=0;
    for (std:: vector<Keyframe*>::iterator it = keyframes.begin(); it != keyframes.end(); it++){
        //std::cout<<"channel"<<i<<std::endl;
        (*it)->computeCoeffcients();
        //std::cout<<""<<std::endl;
        i++;
    }
}

float Channel::eval(float t){
    float starttime=keyframes.front()->getTime();
    float endtime=keyframes.back()->getTime();
    float startval=keyframes.front()->getValue();
    float endval=keyframes.back()->getValue();

    float result;
    //std::cout<<"channel size "<<keyframes.size()<<std::endl;
    if(keyframes.size()<=1){
        result=startval;
    }
    else if(t<starttime){
        if(extrapolateIn==0){
            result=startval;
        }else if(extrapolateIn==1){
            float tangent=keyframes.front()->getTanOut();
            result=startval-tangent*(starttime-t);
        }else if(extrapolateIn==2){
            int cnt=-(starttime-t)/(endtime-starttime)-1;
            float tempt=t-cnt*(endtime-starttime);
            result=interpolate(tempt);
        }else if(extrapolateIn==3){
            int cnt=-(starttime-t)/(endtime-starttime)-1;
            float tempt=t-cnt*(endtime-starttime);
            float tempresult=interpolate(tempt);
            result=tempresult+cnt*(endval-startval);
        }else if(extrapolateIn==4){
            int cnt=-(starttime-t)/(endtime-starttime)-1;
            int dir=(-cnt)%2;
            float tempt;
            if(dir==0){
                tempt=t-cnt*(endtime-starttime);
            }
            else{
                tempt=endtime-(t-cnt*(endtime-starttime)-starttime);
            }
            result=interpolate(tempt);
        }
    }
    else if(endtime<t){
        if(extrapolateIn==0){
            result=endval;
        }else if(extrapolateIn==1){
            float tangent=keyframes.back()->getTanIn();
            result=endval+tangent*(t-endtime);
        }else if(extrapolateIn==2){
            int cnt=(t-starttime)/(endtime-starttime);
            float tempt=t-cnt*(endtime-starttime);
            result=interpolate(tempt);
        }else if(extrapolateIn==3){
            int cnt=(t-starttime)/(endtime-starttime);
            float tempt=t-cnt*(endtime-starttime);
            float tempresult=interpolate(tempt);
            result=tempresult+cnt*(endval-startval);
        }else if(extrapolateIn==4){
            int cnt=(t-starttime)/(endtime-starttime);
            int dir=(cnt)%2;
            float tempt;
            if(dir==0){
                tempt=t-cnt*(endtime-starttime);
            }
            else{
                tempt=endtime-(t-cnt*(endtime-starttime)-starttime);
            }
            result=interpolate(tempt);
        }
    }
    else{
        //std::cout<<""<<std::endl;
        //std::cout<<"channel time "<<t<<std::endl;
        
        result=interpolate(t);
        //std::cout<<"channel value"<<result<<std::endl;
        //std::cout<<""<<std::endl;
    }
    return result;
}

float Channel::interpolate(float t){
    int idx=0;
    int interpolateFlag=0;
    for(std:: vector<Keyframe*>::iterator it = keyframes.begin(); it != keyframes.end(); it++){
        if((*it)->getTime()==t){
            interpolateFlag=1;
            break;
        }else if(t<(*it)->getTime()){
            //std::cout<<"should occur"<<t<<std::endl;
            idx--;
            break;
        }else{
            idx++;
        }
    }
    if(interpolateFlag==0){
        //std::cout<<"should occur with index "<< idx<<std::endl;
        glm::vec4 coeffs=keyframes.at(idx)->getCoef();
        float winstart=keyframes.at(idx)->getTime();
        float winend=keyframes.at(idx+1)->getTime();
        float scaledt=(t-winstart)/(winend-winstart);
        /* std::cout<<""<<std::endl;
        std::cout<<"scaled t "<<scaledt<<std::endl;
        std::cout<<"winstart"<<winstart<<std::endl;
        std::cout<<"winend"<<winend<<std::endl;
        std::cout << glm::to_string(coeffs) << std::endl;
        std::cout<<""<<std::endl; */
        float result=coeffs.x*pow(scaledt,3)+coeffs.y*pow(scaledt,2)+coeffs.z*scaledt+coeffs.w;
        return result;
    }else{
        return keyframes.at(idx)->getValue();
    }
}