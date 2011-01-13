#pragma once

namespace PW
{
	namespace Texture
	{
		public ref struct Vertex
		{
			double X;
			double Y;
			double Z;
			double NX;
			double NY;
			double NZ;
			double U;
			double V;
			Drawing::Color Color;
		};
	}
}