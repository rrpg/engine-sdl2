#ifndef __ACTOR__
#define __ACTOR__

class Actor {
	private:
	int m_iX = 0;
	int m_iY = 0;

	public:
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
};

#endif
