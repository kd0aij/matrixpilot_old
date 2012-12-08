// This file is released under the 3-clause BSD license. See COPYING-BSD.
// Generated by builder.sce : Please, do not edit this file
// ----------------------------------------------------------------------------
//
mavlink_receive_path = get_absolute_file_path('loader.sce');
//
// ulink previous function with same name
[bOK, ilib] = c_link('mavlink_receive');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('startServer');
if bOK then
  ulink(ilib);
end
//
[bOK, ilib] = c_link('imu_basics');
if bOK then
  ulink(ilib);
end
//
link(mavlink_receive_path + 'libmavlink_receive' + getdynlibext(), ['mavlink_receive','startServer','imu_basics'],'c');
// remove temp. variables on stack
clear mavlink_receive_path;
clear bOK;
clear ilib;
// ----------------------------------------------------------------------------
