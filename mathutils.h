template <typename  T>
static inline  T clamp(T val, T min, T max)
{
	return val > max ? max
		: val < min ? min
		: val;
}

template <typename  T>
static inline  T lerp(T A, T B, float t)
{
	return (1.0f - t) * A + t * B;
}