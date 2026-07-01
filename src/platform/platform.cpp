// General platform interface
export module platform;

/*
    We only have the declarations here as the more specialized modules will
   contain the implementations of these functions based on the internal state
   specific to them
*/
export namespace engine::platform
{
struct PlatformState
{
  void *internal_state;
};

bool init (PlatformState *platform_state, const char *window_name, int pos_x,
           int pos_y, int width, int height);

void shutdown (PlatformState *platform_state);

bool update (PlatformState *platform_state);
}