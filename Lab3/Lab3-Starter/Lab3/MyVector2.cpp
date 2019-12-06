#include "MyVector2.h"

/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x ) + (t_vector.y * t_vector.y);
	const float length = std::sqrt(sumOfSquares);
	return length;
}

float vectorLengthSquared(sf::Vector2f t_vector)
{
	//x2 + y2
	float sumOfSquares = (t_vector.x * t_vector.x) + (t_vector.y * t_vector.y);
	return sumOfSquares;
}

float vectorCorssProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	//Vx * Uy - Vy * Ux
	float sumCrossProduct = (t_vectorA.x * t_VectorB.y) - (t_VectorB.x * t_vectorA.y);
	return sumCrossProduct;
}

float vectorDotProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	// Vx * Ux + Vy * Uy
	float sumDotProduct = (t_vectorA.x * t_VectorB.x) + (t_vectorA.y * t_VectorB.y);
	return sumDotProduct;
}

float vectorAngleBetween(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float sum = vectorDotProduct(vectorUnitVector(t_vectorA), vectorUnitVector(t_VectorB));
	if (sum > 1.0f)
	{
		sum = 1.0f;
	}
	if (sum < -1.0f)
	{
		sum = -1.0f;
	}
	float angle = std::acos(sum);
	float answer = angle * 180.0f / PI;
	return answer;
}

sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians)
{
	float xCoord = (t_vector.x * cos(t_angleRadians)) - (t_vector.y * sin(t_angleRadians));
	float yCoord = (t_vector.x * sin(t_angleRadians)) + (t_vector.y * cos(t_angleRadians));
	return sf::Vector2f(xCoord, yCoord);
}


sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float scale = vectorDotProduct(t_vector, t_onto) / vectorLengthSquared(t_onto);
	sf::Vector2f answer = t_onto * scale;
	return answer;
}

sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f answer = t_vector - vectorProjection(t_vector, t_onto);
	return answer;
}

float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float answer = vectorDotProduct(t_vector, t_onto) / vectorLength(t_onto);
	return answer;
}

sf::Vector2f vectorUnitVector(sf::Vector2f t_vector)
{
	//Vector divide by length
	float sumOfSquares = (t_vector.x * t_vector.x) + (t_vector.y * t_vector.y);
	float magnitude = std::sqrt(sumOfSquares);
	float x = t_vector.x / magnitude;
	float y = t_vector.y / magnitude;
	return sf::Vector2f(x, y);
}
