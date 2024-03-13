# Cascading Presets

Presets are cascading; they can take or give precedence over other presets:

* Latest takes priority (`LTP`)<br>
  A later preset takes priority over previous presets.
* Lowest takes priority (`LoTP`)<br>
  When a preset with a lower value than the current preset is already active, that preset will take priority, even if it comes before the current preset.
* Highest takes priority (`HTP`)<br>
  When a preset with a higher value than the current preset is already active, that preset will take priority, even if it comes before the current preset.

This allows you to define intricate lighting that takes priority over other modes when needed, but not interfere with other modes when that is not desirable.

Since what you can do with cascading can be a bit hard to grasp, the following examples will make use of different kinds of cascading to hopefully make it understandable as a useful tool.
