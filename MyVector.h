#pragma once

	template <class T>
	
	class Myvector {
		private:
			unsigned int my_size;
			unsigned int my_capacity;
			T* buffer;

		public:

			typedef T* iterator;

			Myvector() {
				my_capacity = 0;
				my_size = 0;
				buffer = 0;
			};
			~Myvector() {
				delete[]buffer;
			};

			void resize(unsigned int size) {
				iterator buf;

				if (size >= my_size) 
				{
					buf = new T[my_size];
					for (int i = 0; i < my_size; i++) buf[i] = buffer[i];
				}
				else
				{
					buf = new T[size];
					for (int i = 0; i < size; i++) buf[i] = buffer[i];
					my_size = size;
				}

				delete[] buffer;
				buffer = new T[size];
				my_capacity = size;
				for (int i = 0; i < my_size; i++) buffer[i] = buf[i];
				delete[] buf;
			};
			T& operator[](unsigned int index) 
			{
				return buffer[index];
			};
	};