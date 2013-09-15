#ifndef EXT__DESCRIBE_H
#define EXT__DESCRIBE_H

template<typename F>
void Describe(std::string description,F f){
	Spec::Instance().LevelUp();
	Spec::Instance().AddApec(description,FunctionType::Describe);
	f();
	Spec::Instance().LevelDown();
	if (Spec::Instance().GetLevel()==0){
		Spec::Instance().Print();
		Spec::Instance().Conclusion();
	}
}
template<typename F>
void It(std::string description,F f){
	Spec::Instance().LevelUp();
	Spec::Instance().AddApec(description,FunctionType::It);
	f();
	Spec::Instance().LevelDown();
}

#endif