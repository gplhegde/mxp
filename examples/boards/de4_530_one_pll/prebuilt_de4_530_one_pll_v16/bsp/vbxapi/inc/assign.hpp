//VBXCOPYRIGHTTAG
#ifndef __ASSIGN_HPP__
#define __ASSIGN_HPP__
#include "expression_width.hpp"
namespace VBX{


	namespace _internal{
		struct vector_length{
#ifndef CHECK_VECTOR_LENGTH
			template<typename T>
			static void check(size_t vector_len,const T&){
				return;
			}
#else
			template<typename T>
			static void check(size_t vector_len,const Vector<T>& v){
				if(v.size != vector_len)
					assert("Vector lengths don't match" && 0);
			}
			template<typename lhs_t,typename rhs_t,vinstr_t instr>
			static void check(size_t vector_len,const bin_op<lhs_t,rhs_t,instr>& b){
				check(vector_len,b.lhs);
				check(vector_len,b.rhs);
			}
			template<typename T>
			static void check(size_t vector_len,const inv_cmv<T>& inv){
				check(vector_len,inv.wrapped);
			}
			static void check(size_t vector_len,const enum_t& ) {}
			static void check(size_t vector_len,vbx_word_t ){}
			static void check(size_t vector_len,vbx_uword_t ){}
#endif //CHECK_VECTOR_LENGTH
		};

		template<typename dest_t,mask_choice is_masked,int dim>
		struct assignment{

			//Bin_Op
			template<typename lhs_t,typename rhs_t,vinstr_t instr,typename btype,int dim1>
			INLINE static void assign(dest_t* dest,int dest_rows,ssize_t dest_inc2,int dest_mats,int dest_inc3,
			                          const bin_op <lhs_t,rhs_t,instr,btype,dim1,NO_ACC >& src,size_t vlen)
			{
				set_vl(vlen);
				typedef typename source_resolve<dest_t,btype>::type src_t;
				vbx_mxp_t *this_mxp = VBX_GET_THIS_MXP();
				src_t* sp=(src_t*)this_mxp->sp;
				typedef typename same_sign_as<dest_t,src_t>::type d_t;

				typeof(resolve<src_t,is_masked>::_resolve(src.rhs,sp,dest_mats,dest_rows,vlen)) srcB=
					resolve<src_t,is_masked>::_resolve(src.rhs,sp,dest_mats,dest_rows,vlen);
				typeof(resolve<src_t,is_masked>::_resolve(src.lhs,sp,dest_mats,dest_rows,vlen)) srcA=
					resolve<src_t,is_masked>::_resolve(src.lhs,sp,dest_mats,dest_rows,vlen);

				if(dim>=2){
					vbx_set_2D(dest_rows,
					           dest_inc2,
					           get_increment2(src.lhs,vlen),
					           get_increment2(src.rhs,vlen));
				}
				if(dim==3){
					vbx_set_3D(dest_mats,
					           dest_inc3,
					           get_increment3(src.lhs,vlen,dest_rows),
					           get_increment3(src.rhs,vlen,dest_rows));
				}
				vbx_func<is_masked,NO_ACC,dim>::func(get_arith<instr>::instr,
				                                             (d_t*)dest,srcA,srcB);
			}
			//bin op accumulate
			template<typename lhs_t,typename rhs_t,vinstr_t instr,typename btype,int dim1>
			INLINE static void assign(dest_t* dest,int dest_rows,ssize_t dest_inc2,int dest_mats,int dest_inc3,
			                          const bin_op <lhs_t,rhs_t,instr,btype,dim1,IS_ACC >& src,size_t vlen)
			{
				int src_len=get_length(src);
				set_vl(src_len);
 				typedef typename source_resolve<dest_t,btype>::type src_t;
				vbx_mxp_t *this_mxp = VBX_GET_THIS_MXP();
				src_t* sp=(src_t*)this_mxp->sp;
				typedef typename same_sign_as<dest_t,src_t>::type d_t;

				typeof(resolve<src_t,is_masked>::_resolve(src.rhs,sp,dest_mats,dest_rows,vlen)) srcB=
					resolve<src_t,is_masked>::_resolve(src.rhs,sp,dest_mats,dest_rows,src_len);
				typeof(resolve<src_t,is_masked>::_resolve(src.lhs,sp,dest_mats,dest_rows,vlen)) srcA=
					resolve<src_t,is_masked>::_resolve(src.lhs,sp,dest_mats,dest_rows,src_len);

				if(dim>=1){
					//do 2d accumulate
					vbx_set_2D(vlen,
					           sizeof(dest_t),
					           get_increment2(src.lhs,vlen),
					           get_increment2(src.rhs,vlen));
				}
				if(dim==2){
					//do 3d accumulate
					vbx_set_3D(dest_rows,
					           dest_inc2,
					           get_increment3(src.lhs,vlen,dest_rows),
					           get_increment3(src.rhs,vlen,dest_rows));
				}
				vbx_func<is_masked,IS_ACC,dim+1>::func(get_arith<instr>::instr,
				                                     (d_t*)dest,srcA,srcB);
			}

			//Vector
			template<typename T>
			INLINE static void assign(dest_t* dest,int dest_rows, ssize_t dest_inc2,int dest_mats,int dest_inc3,
			                          const Vector<T,dim>& src,size_t vlen)
			{
				typedef typename same_sign_as<dest_t,T>::type d_t;
				set_vl(vlen);
				if(dim>=2){
					vbx_set_2D(dest_rows,dest_inc2,src.increment2,0);
				}
				if(dim==3){
					vbx_set_3D(dest_mats,dest_inc3,src.increment3,0);
				}

				vbx_func<is_masked,NO_ACC,dim>::func(VMOV,(d_t*)dest,src.data);
			}
			//enum
			INLINE static void assign(dest_t* dest,int dest_rows, ssize_t dest_inc2,int dest_mats,int dest_inc3,
			                          const enum_t& src,size_t vlen){
				set_vl(vlen);
				if(dim>=2){
					vbx_set_2D(dest_rows,dest_inc2,0,0);
				}
				if(dim==3){
					vbx_set_3D(dest_mats,dest_inc3,0,0);
				}

				vbx_func<is_masked,NO_ACC,dim>::func(VOR,dest,(vbx_word_t)0,(vbx_enum_t*)0);
			}
			//scalar
			INLINE static void assign(dest_t* dest,int dest_rows, ssize_t dest_inc2,int dest_mats,int dest_inc3,
			                          typename word_sized<dest_t>::type src,size_t vlen){
				set_vl(vlen);
				if(dim>=2){
					vbx_set_2D(dest_rows,dest_inc2,0,0);
				}
				if(dim==3){
					vbx_set_3D(dest_mats,dest_inc3,0,0);
				}

				vbx_func<is_masked,NO_ACC,dim>::func(VMOV,dest,src);
			}

			///////////////////
			// Conditional move
			////////////////////
			//bin_op
			template<typename if_t,typename then_t>
			INLINE static void cond_move(dest_t* data,
			                             const  if_t& v_if,
			                             const then_t& v_then,
			                             size_t dest_mats,ssize_t dest_inc3,
			                             size_t dest_rows,ssize_t dest_inc2,size_t vlen)
			{
				typedef typename get_op_size<if_t>::type t1;
				typedef typename get_op_size<then_t>::type t2;
				typedef typename types_are_equivalent<t1,t2>::type btype;
				typedef typename source_resolve<dest_t,btype>::type src_t;
				typedef typename same_sign_as<dest_t,src_t>::type d_t;
				vbx_mxp_t *this_mxp = VBX_GET_THIS_MXP();
				src_t* sp=(src_t*)this_mxp->sp;
				vinstr_t cmv=get_cmv(v_if);

				set_vl(vlen);
				typeof(resolve<src_t,is_masked>::_resolve(v_then,sp,dest_mats,dest_rows,vlen)) srcA=
					resolve<src_t,is_masked>::_resolve(v_then,sp,dest_mats,dest_rows,vlen);
				typeof(resolve<src_t,is_masked>::_resolve(v_if,sp,dest_mats,dest_rows,vlen)) srcB=
					resolve<src_t,is_masked>::_resolve(v_if,sp,dest_mats,dest_rows,vlen);

				if(dim>=2){
					vbx_set_2D(dest_rows,
					           dest_inc2,
					           get_increment2(v_then,vlen),
					           get_increment2(v_if,vlen));
				}

				vbx_func<is_masked,NO_ACC,dim>::func(cmv,
				                                     (d_t*)data,
				                                     srcA,
				                                     srcB);
			}
			//Logical op
			template<typename lhs_t,typename rhs_t,log_op_t lop,bool negate,typename then_t>
			INLINE static void cond_move(dest_t* data,
			                             const Logical_vop<lhs_t,rhs_t,lop,negate> v_if,
			                             const then_t& v_then,
			                             size_t dest_mats,ssize_t dest_inc3,
			                             size_t dest_rows,ssize_t dest_inc,size_t vlen)
			{
				typedef typename get_op_size<typeof(v_if)>::type t1;
				typedef typename get_op_size<then_t>::type t2;
				typedef typename types_are_equivalent<t1,t2>::type btype;
				typedef typename source_resolve<dest_t,btype>::type src_t;
				typedef typename same_sign_as<dest_t,src_t>::type d_t;

				vbx_mxp_t *this_mxp = VBX_GET_THIS_MXP();
				src_t* sp=(src_t*)this_mxp->sp;
				vinstr_t cmv=get_cmv(v_if);

				set_vl(vlen);
				vbx_func<is_masked,NO_ACC,1>::func(cmv,
				                                   (d_t*)data,
				                                   resolve<src_t,is_masked>::_resolve(v_then,sp,0,0,vlen),
				                                   resolve_logical<src_t,is_masked,NONE>::resolve(v_if,sp,vlen));
			}

		};
	}//namespace _internal
}//namespace VBX
#endif //__ASSIGN_HPP__
