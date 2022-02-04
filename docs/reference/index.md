# Reference

## Events

Events are [weak functions](https://en.wikipedia.org/wiki/Weak_symbol) that can be used in your configuration to react to changes in the main program loop.

Default return values of non-overridden events with a `bool` return type return `true`.

### onInitialize

Called at end of default initialization. Run any config-specific initialization in this callback.

**Usage:**

```cpp
bool onInitialize()
{
  // if (error) return false;
  return true;
}
```

**Arguments:** None.

**Return type**: `bool` — To stop execution after an initialization error, return `false`.

### onUpdate

Called at end of each `loop()` iteration. Run any config-specific initialization for in this callback.

**Usage:**

```cpp
void onUpdate()
{
  // Foo.
}
```

**Arguments:** None.

**Return type**: `void`

### onLightingModeChanged

Called when a [`mode`](/guide/#modes) is about to change state. Channels are only recalculated when the event handler returns `true`. New mode state can be accessed using the modes `nextState` property.

**Usage:**

```cpp
bool onLightingModeChanged(int modeID)
{
  LightingMode &mode = modes[i];
  if (mode.currentState < mode.nextState)
  {
    // Foo.
  }
  return true;
}
```

**Arguments:**

- `int` `modeID` — ID of the mode that changed.

**Return type**: `bool` — To discard the mode change, return `false`.

### onBlinkPhaseChanged

Called whenever a `Channel` that is currently in `Blink` mode changes blink phase.

**Usage:**

```cpp
bool onBlinkPhaseChanged(Channel &channel)
{
  // return false // Prevent blink phase change.
  return true; // Allow blink phase change.
}
```

**Arguments:**

- `Channel` `&channel` — Channel reference which blink phase changed.

**Return type**: `bool` — To discard the blink phase change, return `false`.

### onSocketConnectionChanged

Called when a websocket client connects or disconnects to the websockets server.

**Usage:**

```cpp
void onSocketConnectionChanged(uint8_t connectedClients)
{
  // Foo.
}
```

**Arguments:**

- `uint8_t` `connectedClients` — Number of connected clients after the connection event.

**Return type**: `void`

### onDeviceConnectionChanged

Called when a `WireDevice` connects or disconnects to the wire bus. In the case of connection, the event is called _after_ the device's `setup()`-routine has run.

**Usage:**

```cpp
void onSocketConnectionChanged(uint8_t connectedClients)
{
  // return false // Don't recalculate channel values.
  return true; // Recalculate channel values.
}
```

**Arguments:**

- `WireDevice` `&device` — Reference to the `WireDevice` that co.

**Return type**: `bool` — To prevent recalculation of [channels](/guide/#channels) return `false`.
