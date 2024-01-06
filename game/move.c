union move{
	struct {
		unsigned int playerId : 8;
		unsigned int moveType : 4;
		unsigned int orentation : 4;
		unsigned int Y : 8;
		unsigned int X : 8;
	}sections;
	
	unsigned int value;
}mv;

void saveMove(unsigned int playerId, unsigned int moveType, unsigned int orentation, unsigned int X, unsigned int Y){
	mv.sections.playerId = playerId;
	mv.sections.moveType = moveType;
	mv.sections.orentation = orentation;
	mv.sections.X = X;
	mv.sections.Y = Y;
}
