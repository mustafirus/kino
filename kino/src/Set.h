#if !defined(SET_H__INCLUDED_)
#define SET_H__INCLUDED_

class RField;
class QField;
class RKey;
#ifdef USE_STD_CONTAINERS

typedef std::vector<RField*> RFields;
typedef std::vector<QField*> QFields;
typedef std::vector<RKey*> RKeys;


#else
typedef Set<RField> RFields;
typedef Set<QField> QFields;
typedef Set<RKey>	RKeys;
#endif //USE_STD_CONTAINERS

#endif // !defined(SET_H__INCLUDED_)
