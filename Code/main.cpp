#include <iostream>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////
struct SGlobePoint
{
    float posX;
    float posY;
    float posZ;
    
    float norX;
    float norY;
    float norZ;
    
    float colR;
    float colG;
    float colB;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
const static float RAD = 6380.0e3f;
const static float A_TO_R_COEF = 0.9510565163f;
const static float CONST_PI = 3.14159f;
////////////////////////////////////////////////////////////////////////////////////////////////////
static float GetIcosahedronArcAngle()
{
    const float c = 2.0f * A_TO_R_COEF * A_TO_R_COEF;
    const float cosinus = ( c - 1 ) / c;
    const float angleRad = acos( cosinus );
    const float angleDeg = angleRad * 180.0f / CONST_PI;
    return angleDeg;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static const float GetEdgeLength( const float angle )
{
    assert( angle >= 0.0f && angle <= 360.0f );
    const float equator = 2.0f * CONST_PI * RAD; 
    const float length = equator * angle / 360.0f;
    return length;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static const int GetPowerOfTwo( const int power )
{
    int mul = 1;
    for( int i = 0; i < power; ++i )
        mul *= 2;
    return mul;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void CalcAndReportMaxPatch()
{
    int triaCount = 1;
    int vertCount = 3;
    int edgeCount = 3;
    int iterCount = 0;
    for( ; ; )
    {
        const int nextT = 4 * triaCount;
        const int nextV = vertCount + edgeCount;
        const int nextE = 2 * edgeCount + 3 * triaCount;
        
        if( nextV > 65536 )
            break;
            
        triaCount = nextT;
        vertCount = nextV;
        edgeCount = nextE;
        
        ++iterCount;
    }
    
    std::cout << "Max patch after " << iterCount << " interation(s) consist of:" << std::endl;
    std::cout << "Triangles: " << triaCount << std::endl;
    std::cout << "Vertices:  " << vertCount << std::endl;
    std::cout << "Edged:     " << edgeCount << std::endl;
    std::cout << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void CalcAndReportMaxIcosahedron( const int iterCount )
{
    uint64_t triaCount = 20;
    uint64_t vertCount = 12;
    uint64_t edgeCount = 30;
    
    for( int i = 0; i < iterCount; ++i )
    {
        const uint64_t nextT = 4 * triaCount;
        const uint64_t nextV = vertCount + edgeCount;
        const uint64_t nextE = 2 * edgeCount + 3 * triaCount;
        
        triaCount = nextT;
        vertCount = nextV;
        edgeCount = nextE;
    }
    
    std::cout << "Whole globe after " << iterCount << " interation(s) consist of:" << std::endl;
    std::cout << "Triangles: " << triaCount << std::endl;
    std::cout << "Vertices:  " << vertCount << std::endl;
    std::cout << "Edged:     " << edgeCount << std::endl;
    std::cout << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout<<"Icosahedron calculation" << std::endl;
    
    const float arcAng = GetIcosahedronArcAngle();
    const float arcLen = GetEdgeLength( arcAng ) / 1000.0f;
    
    std::cout << std::endl;
    std::cout << "Angle of initial arc: " << arcAng << "° and " << arcLen << " km. " << std::endl;
    int iterCount = 1;
    for( ; ; )
    {
        const int divider = GetPowerOfTwo( iterCount );
        const float ang = arcAng / static_cast< float >( divider );
        const float len = GetEdgeLength( ang ) / 1000.0f;
        std::cout << "At iteration " << iterCount << " angle is " << ang << " and length is " << len << "km." << std::endl;
        ++iterCount;
        
        if( len < 0.1f )
            break;
    }
    
    CalcAndReportMaxPatch();
    CalcAndReportMaxIcosahedron( 16 );
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////