#ifndef __GGABSTRACTOBSERVER_H
#define __GGABSTRACTOBSERVER_H

class GGAbstractObserver {
public:
	virtual ~GGAbstractObserver() {}
	virtual void Update() = 0;
};

#endif