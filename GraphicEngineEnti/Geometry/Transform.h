#pragma once
class Transform
{

  glm::quat  rot;
  glm::vec3  pos;
  float scale = 1.0f;
 
public:
  Transform();
  glm::quat getRotation() const { return rot; }
  void setRotation(glm::quat new_rot) { rot = new_rot; }
  glm::vec3 getPosition() const { return pos; }
  void setPosition(glm::vec3 new_pos) { pos = new_pos; }
  void addPosition(glm::vec3 delta) { pos += delta; }
  void setScale(float new_scale) { scale = new_scale; }
  float getScale() const { return scale; }
  glm::vec3 getFront() const;
  glm::vec3 getLeft() const;
  glm::mat4 asMatrix() const;
  void setEulerAngles(float yaw, float pitch, float roll);
  glm::vec3& getEulerAngles();


 float getDeltaYawToAimTo(glm::vec3 p) const;
 bool isInCone(glm::vec3 p, float half_cone) const;



};

