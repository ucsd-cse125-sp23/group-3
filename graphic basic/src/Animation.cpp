#include "Animation.h"

Animation::Animation(){
    this->channels=std::vector<Channel*>();
    this->timestart=0;
    this->timeend=0;
    this->numchan=0;
}

Animation:: ~Animation(){

}

void Animation::load(const char* file){
    Tokenizer token=Tokenizer();
    token.Open(file);
    char temp[256];
    token.GetToken(temp);
    token.GetToken(temp);
    token.GetToken(temp);
    //std::cout<< "start load" <<std::endl;
    if (strcmp(temp,"range")==0){
        this->timestart=token.GetFloat();
        this->timeend=token.GetFloat();
    }
    token.GetToken(temp);
    int numchannels;
    if(strcmp(temp,"numchannels")==0){
        numchannels=token.GetInt();
        this->numchan=numchannels;
    }
    //std::cout<< "loading phase 1" <<std::endl;
    for(int i=0;i<numchannels;i++){
        token.GetToken(temp);
        if(strcmp(temp,"channel")==0){
            //std::cout<< "loading phase 2" <<std::endl;
            token.GetFloat();
            token.GetToken(temp);
            token.GetToken(temp);
            int expIn,expOut,numkeys;
            if(strcmp(temp,"extrapolate")==0){
                //std::cout<< "loading phase 3" <<std::endl;
                token.GetToken(temp);
                if(strcmp(temp,"constant")==0){
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
                token.GetToken(temp);
                if(strcmp(temp,"constant")==0){
                    expOut=0;
                }else if(strcmp(temp,"linear")==0){
                    expOut=1;
                }else if(strcmp(temp,"cycle")==0){
                    expOut=2;
                }else if(strcmp(temp,"cycle_offset")==0){
                    expOut=3;
                }else if(strcmp(temp,"bounce")==0){
                    expOut=4;
                }
            }
            token.GetToken(temp);
            numkeys=token.GetInt();
            Channel* newChannel=new Channel(expIn,expOut,numkeys);
            token.GetToken(temp);
            //std::cout<< "loading phase 4" <<std::endl;
            for(int j=0;j<numkeys;j++){
                float time=token.GetFloat();
                float value=token.GetFloat();
                int rulein,ruleout;
                float tanin=0;
                float tanout=0;
                if(!isdigit(token.CheckChar())){
                    //std::cout<< "loading phase 5" <<std::endl;
                    token.GetToken(temp);
                    if(strcmp(temp,"flat")==0){
                        rulein=1;
                    }else if(strcmp(temp,"linear")==0){
                        rulein=2;
                    }else if(strcmp(temp,"smooth")==0){
                        rulein=3;
                    }
                    //std::cout<< temp <<std::endl;
                }
                else{
                    rulein=0;
                    tanin=token.GetFloat();
                }
                if(!isdigit(token.CheckChar())){
                    //std::cout<< temp <<std::endl;
                    token.GetToken(temp);
                    //std::cout<< temp <<std::endl;
                    if(strcmp(temp,"flat")==0){
                        ruleout=1;
                    }else if(strcmp(temp,"linear")==0){
                        ruleout=2;
                    }else if(strcmp(temp,"smooth")==0){
                        ruleout=3;
                    }
                }
                else{
                    ruleout=0;
                    tanout=token.GetFloat();
                }
                
                Keyframe* newframe=new Keyframe(time,value,rulein,ruleout,tanin,tanout);
                //std::cout<< "loading phase 6" <<std::endl;
                newChannel->addFrame(newframe);
                
            }
            token.GetToken(temp);
            this->channels.push_back(newChannel);
            //std::cout<< temp <<std::endl;
        }
        token.GetToken(temp);
    }
    token.Close();
    //std::cout<< "end load" <<std::endl;
    int idx;
    for (std:: vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++){
        //std::cout<<"load channel "<<idx<<std::endl;
        (*it)->load();
        idx++;
    }
}

void Animation::update(float t){
    /* int count=(t-timestart)/(timeend-timestart);
    float newtime=t-count*(timeend-timestart); */
    float newtime=t;
    if(this->numchan>0){
        this->jntlist=Joint::getList();
        //std::cout<<"update start"<<std::endl;
        //std::cout<<channels.size()<<std::endl;
        for(int i=0;i<numchan;i++){
            float value=channels.at(i)->eval(newtime);;
            /* if(i==2){
                std::cout<<"update channel "<<i<<std::endl;
                std::cout<<"with time "<<t<<std::endl;
                std::cout<<"with value "<<value<<std::endl;
            }  */
            if(i<3){
                jntlist.at(0)->setOffset(value,i);
            }
            else{
                int jntnum=(i-3)/3;
                int dofidx=(i-3)-jntnum*3;
                jntlist.at(jntnum)->getDOF()->SetValueSp(value,dofidx);
            }
        }
    }
}