#ifndef _SINGLETON_H__
#define _SINGLETON_H__
namespace imp {
	template <typename T>
	class Singleton {
	private:
		struct object_creator {
			object_creator()
			{
				Singleton<T>::instance();
			}
			inline void do_nothing() const {}
		};
		static object_creator create_object_;
	public:
		static T* instance()
		{
			static T obj;
			create_object_.do_nothing();
			return &obj;
		}
	};
	template <typename T> typename Singleton<T>::object_creator Singleton<T>::create_object_;
}
#endif /* _SINGLETON_H__ */
