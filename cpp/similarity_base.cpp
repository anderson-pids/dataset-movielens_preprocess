#include "similarity_base.h"

similarity_base::similarity_base()
{
}

similarity_base::~similarity_base()
{

}

void similarity_base::SetMatrix(mat *ratings)
{
	mRatings = ratings;
	mSim = new mat(mRatings->size());
}

void similarity_base::SetSecElementsSize(int secElementSize)
{
	mSecElementSize = secElementSize;
}

mat* similarity_base::GetMatrix()
{
	return mSim;
}