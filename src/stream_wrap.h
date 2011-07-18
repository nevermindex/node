#ifndef STREAM_WRAP_H_
#define STREAM_WRAP_H_

namespace node {

class StreamWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);

  // JavaScript functions
  static v8::Handle<v8::Value> Write(const v8::Arguments& args);
  static v8::Handle<v8::Value> ReadStart(const v8::Arguments& args);
  static v8::Handle<v8::Value> ReadStop(const v8::Arguments& args);
  static v8::Handle<v8::Value> Shutdown(const v8::Arguments& args);
  static v8::Handle<v8::Value> Close(const v8::Arguments& args);

 protected:
  StreamWrap(v8::Handle<v8::Object> object, uv_stream_t* stream);
  ~StreamWrap();

  v8::Persistent<v8::Object> object_;

 private:
  void UpdateWriteQueueSize();
  static inline char* NewSlab(v8::Handle<v8::Object> global, v8::Handle<v8::Object> wrap_obj);

  // Callbacks for libuv
  static void AfterWrite(uv_write_t* req, int status);
  static uv_buf_t OnAlloc(uv_stream_t* handle, size_t suggested_size);
  static void OnRead(uv_stream_t* handle, ssize_t nread, uv_buf_t buf);
  static void AfterShutdown(uv_shutdown_t* req, int status);
  static void OnClose(uv_handle_t* handle);

  size_t slab_offset_;
  uv_stream_t* stream_;
};


}  // namespace node


#endif  // STREAM_WRAP_H_
