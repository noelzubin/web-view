#ifndef WEBVIEW_H
#define WEBVIEW_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WEBVIEW_STATIC
#define WEBVIEW_API static
#else
#define WEBVIEW_API extern
#endif

#include <stdint.h>
#include <string.h>

struct webview;

typedef void (*webview_external_invoke_cb_t)(struct webview *w, const char *arg);
typedef void (*webview_dispatch_fn)(struct webview *w, void *arg);

WEBVIEW_API int webview(const char *title, const char *url, int width,
                        int height, int resizable);

WEBVIEW_API int webview_init(struct webview *w);
WEBVIEW_API int webview_loop(struct webview *w, int blocking);
WEBVIEW_API int webview_eval(struct webview *w, const char *js);
WEBVIEW_API int webview_inject_css(struct webview *w, const char *css);
WEBVIEW_API void webview_set_title(struct webview *w, const char *title);
WEBVIEW_API void webview_set_fullscreen(struct webview *w, int fullscreen);
WEBVIEW_API void webview_set_color(struct webview *w, uint8_t r, uint8_t g,
                                   uint8_t b, uint8_t a);
WEBVIEW_API void webview_dialog(struct webview *w,
                                enum webview_dialog_type dlgtype, int flags,
                                const char *title, const char *arg,
                                char *result, size_t resultsz);
WEBVIEW_API void webview_dispatch(struct webview *w, webview_dispatch_fn fn,
                                  void *arg);
WEBVIEW_API void webview_terminate(struct webview *w);
WEBVIEW_API void webview_exit(struct webview *w);
WEBVIEW_API void webview_debug(const char *format, ...);
WEBVIEW_API void webview_print_log(const char *s);

WEBVIEW_API void* wrapper_webview_get_userdata(struct webview* w);
WEBVIEW_API struct webview* wrapper_webview_new(const char* title, const char* url, int width, int height, int resizable, int debug, webview_external_invoke_cb_t external_invoke_cb, void* userdata);
WEBVIEW_API void wrapper_webview_free(struct webview* w);

enum webview_dialog_type {
  WEBVIEW_DIALOG_TYPE_OPEN = 0,
  WEBVIEW_DIALOG_TYPE_SAVE = 1,
  WEBVIEW_DIALOG_TYPE_ALERT = 2
};

#define WEBVIEW_DIALOG_FLAG_FILE (0 << 0)
#define WEBVIEW_DIALOG_FLAG_DIRECTORY (1 << 0)

#define WEBVIEW_DIALOG_FLAG_INFO (1 << 1)
#define WEBVIEW_DIALOG_FLAG_WARNING (2 << 1)
#define WEBVIEW_DIALOG_FLAG_ERROR (3 << 1)
#define WEBVIEW_DIALOG_FLAG_ALERT_MASK (3 << 1)

struct webview_dispatch_arg {
  webview_dispatch_fn fn;
  struct webview *w;
  void *arg;
};

#define DEFAULT_URL                                                            \
  "data:text/"                                                                 \
  "html,%3C%21DOCTYPE%20html%3E%0A%3Chtml%20lang=%22en%22%3E%0A%3Chead%3E%"    \
  "3Cmeta%20charset=%22utf-8%22%3E%3Cmeta%20http-equiv=%22X-UA-Compatible%22%" \
  "20content=%22IE=edge%22%3E%3C%2Fhead%3E%0A%3Cbody%3E%3Cdiv%20id=%22app%22%" \
  "3E%3C%2Fdiv%3E%3Cscript%20type=%22text%2Fjavascript%22%3E%3C%2Fscript%3E%"  \
  "3C%2Fbody%3E%0A%3C%2Fhtml%3E"

#define CSS_INJECT_FUNCTION                                                    \
  "(function(e){var "                                                          \
  "t=document.createElement('style'),d=document.head||document."               \
  "getElementsByTagName('head')[0];t.setAttribute('type','text/"               \
  "css'),t.styleSheet?t.styleSheet.cssText=e:t.appendChild(document."          \
  "createTextNode(e)),d.appendChild(t)})"

static inline const char *webview_check_url(const char *url) {
  if (url == NULL || strlen(url) == 0) {
    return DEFAULT_URL;
  }
  return url;
}

#ifdef __cplusplus
}
#endif

#endif // WEBVIEW_H