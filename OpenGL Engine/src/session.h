#pragma once

struct Session {

	virtual ~Session() { };

	virtual void preUpdate() { };
	virtual void update() = 0;
	virtual void postUpdate() { };

	virtual void render() { };

};