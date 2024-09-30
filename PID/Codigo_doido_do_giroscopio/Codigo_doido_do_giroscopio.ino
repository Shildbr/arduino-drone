  total_angle = sqrt((angleX*angleX)+(angleY*angleY)+(angleZ*angleZ));

  angle_pitch = asin((float)angleX/total_angle) * 57.296;
  angle_row = asin((float)angleY/total_angle) * -57.296;